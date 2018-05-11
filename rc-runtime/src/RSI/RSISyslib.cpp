
#include "RSISyslib.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "opmanager.hh"

bool RSIStopFlag = true; /* THIS IS VERY IMPORTANT, WHICH CONTROL THE WHOLE LIFECYCLE OF RSI */
int  sockfd;	
// #define RSI_DEBUG

#ifdef RSI_DEBUG_PRINT
std::unordered_map<int, std::string> rdataIndexMap;   // index --> var
#endif

// 增量式PID辅助函数
inline int PIDcoe(IValue Kp,IValue Ki,IValue Kd,std::vector<IValue>& coe){
	coe[0] = Kp+Ki+Kd;
	coe[1] = -(Kp+2*Kd);
	coe[2] = Kd;
}

inline int rsi_pid(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	EntityPID *entity = dynamic_cast<EntityPID*>(config);
	if(entity != NULL) {
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
		// if(params.size() != 2){
		// 	std::cout << "wrong nums of parameters" << std::endl;
		// 	rc_fb_lackofconfig_exception("PID");
		// }
		vector<IValue> Coe(3);
		PIDcoe(entity->kp,entity->ki,entity->kd,Coe);
		entity->prev = entity->prev + Coe[0] * addrspace[params[0]] + Coe[1]*entity->prevErr + Coe[2]*entity->pprevErr;
		entity->pprevErr = entity->prevErr;
		entity->prevErr = addrspace[params[0]];	
		// addrspace[params[1]] = entity->prev;
		addrspace[params[0]] = entity->prev;
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
		rc_fb_lackofconfig_exception("PID");
	}
	return 0;
}

inline int rsi_pidn(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace){
	EntityPIDn *entity = dynamic_cast<EntityPIDn*>(config);
	if(entity != NULL){
	#ifdef RSI_DEBUG
		entity->printInfo();
	#endif
		size_t Cnt = entity->SeqCnt;
		// if(params.size() != Cnt*2){
		// 	std::cout << "wrong nums of parameters" << std::endl;
		// 	rc_fb_lackofconfig_exception("PIDN");
		// }
		std::vector<IValue> Coe(3);
		PIDcoe(entity->kp,entity->ki,entity->kd,Coe);
		// for(size_t i = 0; i < 3; ++i)
		// 	std::cout << "coe" << i << " " << Coe[i] << std::endl;
		for(size_t i = 0; i != Cnt; ++i){
			entity->prevSeq[i] = entity->prevSeq[i] + Coe[0] * addrspace[params[i]] + Coe[1]*entity->prevErr[i] + Coe[2]*entity->pprevErr[i];
			entity->pprevErr[i] = entity->prevErr[i];
			entity->prevErr[i] = addrspace[params[i]];	
			// addrspace[params[i+Cnt]] = entity->prevSeq[i];
			addrspace[params[i]] = entity->prevSeq[i];
		}	
	}else {
		std::cout << "this fb does not have config entity" << std::endl;
		rc_fb_lackofconfig_exception("PIDN");
	}
	return 0;
}

// 设置传感器零点偏移
inline int rsi_setoffset(std::vector<int>& params, EntityBase* config,std::vector<IValue>& addrspace)
{
	EntitySETOFFSET * entity = dynamic_cast<EntitySETOFFSET*>(config);
	if(entity != NULL){
#ifdef RSI_DEBUG
		entity->printInfo();
		std::cout << "I am coming in set offset" << std::endl;
#endif
		size_t cnt = entity->listCnt;
		if(params.size() != 2*cnt){
			std::cout << "wrong nums of parameters" << std::endl;
			rc_fb_lackofconfig_exception("SETOFFSEST");
		}
		if(entity->filterCnt <= entity->filterCfg){
			// std::cout << "In set offset and cnt = " << entity->filterCnt << std::endl; 
			addrspace[0] = IValue(0);
			if(entity->offlist.empty()){
				std::cout << "the first time " << entity->filterCnt << std::endl;
				entity->offlist.resize(cnt);
				entity->maxlist.resize(cnt);
				entity->minlist.resize(cnt);
				for(int i = 0; i < cnt; ++i){
					entity->offlist[i] = addrspace[params[i]];
					entity->maxlist[i] = addrspace[params[i]];
					entity->minlist[i] = addrspace[params[i]];
				}
			}else{
				for(size_t i = 0; i != cnt; ++i){
					entity->offlist[i] += addrspace[params[i]];
					if(addrspace[params[i]] < entity->minlist[i]) entity->minlist[i] = addrspace[params[i]];
					if(addrspace[params[i]] > entity->maxlist[i]) entity->maxlist[i] = addrspace[params[i]];
				}
			}
			if(entity->filterCnt == entity->filterCfg){
				std::cout << "the Last time " << entity->filterCnt << std::endl;
				addrspace[0] = IValue(0);
				for(size_t i = 0; i != cnt; ++i){
					entity->offlist[i] = (entity->offlist[i]-entity->maxlist[i]-entity->minlist[i])/(entity->filterCfg-2);
					addrspace[params[i+cnt]] = entity->offlist[i];
				}
			}
			++entity->filterCnt;
#ifndef RSI_DEBUG
			send_cmd_to_rsi(1);
#endif
		}else{
			// sub the offset
			for(size_t i = 0; i < cnt; ++i)
				addrspace[params[i]] -= addrspace[params[i+cnt]];
			addrspace[0] = IValue(1);
			// addrspace[params.back()] = IValue(true);
			// std::cout << params.back() << "\t" << addrspace[params.back()];
			return 0;
		} 
	}
	else {
		std::cout << "this fb does not have config entity" << std::endl;
		rc_fb_lackofconfig_exception("SETOFFSET");
	}
	return 0;
}


inline int rsi_comm_interface(std::vector<int>& params, EntityBase* config, 
							  std::vector<IValue>& addrspace) 
{
	EntityComm *entity = dynamic_cast<EntityComm*>(config);
	if(entity != NULL) {
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
		throw rc_fb_lackofconfig_exception("COMMUNICATION");
	}
	if(entity->stype == SENSOR && entity->cycflag == false){
		if(entity->cfgruncnt < entity->cfgcmdcnt){
			int len = entity->genSendPackage(addrspace);
    		std::cout << (unsigned)entity->sendBuffer;
    		int sn = sendto(sockfd, entity->sendBuffer, len, 0, (struct sockaddr *)&entity->sensoraddr, sizeof(entity->sensoraddr));
   	 		std::cout << "send ==> " << sn << " bytes and have sent " << entity->cfgruncnt+1 << " packages"<< std::endl;
   	 	}
   	 	++ entity->cfgruncnt;
   	 	if(entity->cfgruncnt >= entity->cfgcmdcnt+3) entity->cycflag = true;
   	 	addrspace[0] = 0;
#ifndef RSI_DEBUG
		send_cmd_to_rsi(1);
#endif
   	 	// send_cmd_to_rsi(1);
   	 }else{ 
    	if(entity->stype == PC || (entity->stype == SENSOR && entity-> smode == CYCLIC)){
    		int len = entity->genSendPackage(addrspace);
    		std::cout << entity->sendBuffer << std::endl;
    		int sn = sendto(sockfd, entity->sendBuffer, len, 0, (struct sockaddr *)&entity->sensoraddr, sizeof(entity->sensoraddr));
   	 		std::cout << "send ==> " << sn << " bytes" << std::endl;
    	}
    	std::cout << "waiting for data ..." << std::endl;
    	int rn = recvfrom(sockfd, entity->recvBuffer, 4096, 0, NULL, NULL);
   	 	if(rn == -1 && errno == EAGAIN) {
    		std::cout << "receive timeout " << std::endl;
    		throw rc_rsicomm_outoftime_exception("rsi_comm_interface");
    	} else {
    		std::cout << "recv <== " << rn << " bytes" << std::endl;
    		std::cout << entity->recvBuffer;
    		entity->parseRecvPackage(addrspace);
    	}
    	addrspace[0] = 1;
    }    
	return 0;
}

extern bool posFirstFlag;
inline int rsi_poscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	EntityPOSCORR *entity = dynamic_cast<EntityPOSCORR*>(config);
	if(entity != NULL) {
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
		if(params.size() == 6) {
			if(addrspace[params[0]] < entity->LowerLimX || addrspace[params[0]] > entity->UpperLimX
				|| addrspace[params[1]] < entity->LowerLimY || addrspace[params[1]] > entity->UpperLimY
				|| addrspace[params[2]] < entity->LowerLimZ || addrspace[params[2]] > entity->UpperLimZ
				) {
				throw rc_exception();
			}
		} else {
			throw rc_wrongparam_exception();
		}

	} else {
		std::cout << "this fb does not have config entity" << std::endl;
		throw rc_fb_lackofconfig_exception("POSCORR");
	}

	// size_t n = pRobot->getRobotAxisNum();
	// /* define a temp robot inst */
	// ROBOT_INST temp_inst;			
	// /* step 1: setting the robot inst type */
	// temp_inst.ri_type = CART_ADJUST;
	// /* step 2: specify the first point(the current position) of CART_ADJUST inst  */	
	// Position_ACS_deg p1(n);
	// pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
	// temp_inst.args[0].apv = p1;
	// /* step 3: specify the second point(the target position) of CART_ADJUST inst  */	
	// Position_MCS_rad p2;				// 待考虑
	// for(int i = 0; i < 6; i ++)
	// 	p2[i] = addrspace[params[i]].RSIDouble();
	// temp_inst.args[1].cpv = p2;
	// /* step 4: setting frame */
	// temp_inst.args[0].jjp.refsys = 2;
	// /* step 5: insert inst into inst-buffer */
	// inst_buffer_write(temp_inst);	
	
	size_t n = pRobot->getRobotAxisNum();
	ROBOT_INST temp_inst;
	temp_inst.ri_type = AXIS_ADJUST;
	/* step 2: specify the first point(the current position) of CART_ADJUST inst  */	
	Position_ACS_deg p1(n);
	if(posFirstFlag){
		pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
		posFirstFlag = false;
	}else
		pRobot->getCommandAxisPos(rc_shm,&rc_mutex_desc,p1);
	temp_inst.args[0].apv = p1;
	// std::cout << " input apv " << p1.transpose() << std::endl;
	// /* step 3: specify the second point(the target position) of CART_ADJUST inst  */	
	// AxisPos_Deg p2(6);

	// for(int i = 0; i < 6; i ++) {
	// 	p2[i] = p1[i] + addrspace[params[i]].RSIDouble();
	// }
	// temp_inst.args[1].apv = p2;
	// /* step 4: setting frame */
	// temp_inst.args[0].jjp.refsys = 0;
	// /* step 5: insert inst into inst-buffer */
	// inst_buffer_write(temp_inst);	

	// just for test
	Position_MCS_deg p2(6);  // 这里需要考虑一下，力传感器传回的　N 和 N*m 怎么转换到工具坐标系的位姿
	for(int i = 0; i < 6; ++i)
		p2[i] = addrspace[params[i]].RSIDouble();
	Position_MCS_rad p2tmp = posMCS_deg2rad(p2);
	// Position_MCS_rad posTCP(6);
	// pRobot->toolRPY2baseRPY(deg2rad(p1),p2tmp,posTCP);
	// Position_ACS_rad Pend(n);
	// pRobot->calcInverseKin_RPY(posTCP,deg2rad(p1),Pend);
	Position_ACS_rad Pend(n);
	pRobot->toolRPY2axisPos(deg2rad(p1),p2tmp,Pend);
	temp_inst.args[1].apv = rad2deg(Pend);
	// std::cout << "Correct Pos = " << p2.transpose() << std::endl;
	// std::cout << "In RSI Original Pos = " << p1.transpose() << std::endl;
	// std::cout << "In RSI Target Pos = " << Pend.transpose() << std::endl;
	temp_inst.args[0].jjp.refsys = 0;
	inst_buffer_write(temp_inst);
	return 0;
}


inline int rsi_axiscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	EntityAXISCORR *entity = dynamic_cast<EntityAXISCORR*>(config);
	if(entity != NULL) {
#ifdef RSI_DEBUG
		entity->printInfo();
#endif
	} else {
		std::cout << "this fb does not have config entity" << std::endl;
		rc_fb_lackofconfig_exception("AXISCORR");
	}	
	size_t n = pRobot->getRobotAxisNum();
	/* define a temp robot inst */
	ROBOT_INST temp_inst;			
	/* step 1: setting the robot inst type */
	temp_inst.ri_type = AXIS_ADJUST;
	/* step 2: specify the first point(the current position) of CART_ADJUST inst  */	
	Position_ACS_deg p1(n);
	if(posFirstFlag){
		pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
		posFirstFlag = false;
	}else
		pRobot->getCommandAxisPos(rc_shm,&rc_mutex_desc,p1);
	temp_inst.args[0].apv = p1;
	// std::cout << " input apv " << p1.transpose() << std::endl;
	// /* step 3: specify the second point(the target position) of CART_ADJUST inst  */	
	// AxisPos_Deg p2(6);

	// for(int i = 0; i < 6; i ++) {
	// 	p2[i] = p1[i] + addrspace[params[i]].RSIDouble();
	// }
	// temp_inst.args[1].apv = p2;
	// /* step 4: setting frame */
	// temp_inst.args[0].jjp.refsys = 0;
	// /* step 5: insert inst into inst-buffer */
	// inst_buffer_write(temp_inst);	

	//============================= ORIGINAL =================================/
	// just for test
	// Position_MCS_deg p2(6);  // 这里需要考虑一下，力传感器传回的　N 和 N*m 怎么转换到工具坐标系的位姿
	// for(int i = 0; i < 6; ++i)
	// 	p2[i] = addrspace[params[i]].RSIDouble();
	// Position_MCS_rad p2tmp = posMCS_deg2rad(p2);
	// // Position_MCS_rad posTCP(6);
	// // pRobot->toolRPY2baseRPY(deg2rad(p1),p2tmp,posTCP);
	// // Position_ACS_rad Pend(n);
	// // pRobot->calcInverseKin_RPY(posTCP,deg2rad(p1),Pend);
	// Position_ACS_rad Pend(n);
	// pRobot->toolRPY2axisPos(deg2rad(p1),p2tmp,Pend);
	// temp_inst.args[1].apv = rad2deg(Pend);
	// // std::cout << "Correct Pos = " << p2.transpose() << std::endl;
	// // std::cout << "In RSI Original Pos = " << p1.transpose() << std::endl;
	// // std::cout << "In RSI Target Pos = " << Pend.transpose() << std::endl;
	// temp_inst.args[0].jjp.refsys = 0;
	// inst_buffer_write(temp_inst);
	//============================= ORIGIANL ======================================//
	for(int i = 0; i < 6; ++i)
		temp_inst.args[1].apv[i] = addrspace[params[i]].RSIDouble();
	temp_inst.args[0].jjp.refsys = 0;
	inst_buffer_write(temp_inst);
	return 0;
}


inline int rsi_posact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	if(params.size() != 6)
		return -1;
	Position_MCS_rad pos(6);
	pRobot->getActualTCPPos(rc_shm,&rc_mutex_desc,pos);
	for(size_t i = 0; i != 6; ++i)
		addrspace[params[i]] = IValue(RSIDOUBLE,pos[i]);
	return 0;
}

inline int rsi_axisact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	size_t n = pRobot->getRobotAxisNum();
	if(params.size() != n) return -1;
	Position_ACS_deg pos(n);	
	pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,pos);
	for(size_t i = 0; i != n; ++i) 
		addrspace[params[i]] = IValue(RSIDOUBLE,pos[i]);
	return 0;
}
