#include "InterpolationInterface.h"
#include "opmanager.hh"
#include <fstream>

extern InterpolationInterface* pInterpolator;
// extern std::shared_ptr<InterpolationInterface> pInterpolator;

//　暂时定义全局变量进行测试
std::deque<Position_ACS_deg> 	PosSeq;
std::deque<Velocity_ACS_deg>    VelSeq;
extern bool INRSIPeriod;

std::ofstream Posdatafile;
std::ofstream Veldatafile;
std::ofstream PosUsedfile;

int interp_compute(ROBOT_INST &temp_inst){
	switch(temp_inst.ri_type){
		case PTP: {
			PosSeq.clear();
			pInterpolator->JointInterp(temp_inst.args[0].apv,temp_inst.args[1].apv,
									rc_core.Ts,rc_core.vper*0.5,rc_core.aper,100,PosSeq);
			if(!PosSeq.empty()){
				SHM_INTERP_STATUS_SET(rc_shm);
				SHM_INTERP_START_SET(rc_shm);
				while(!PosSeq.empty()){
					// std::cout << PosSeq.front().transpose() << std::endl;
					interp_step(PosSeq.front());
					PosSeq.pop_front();
				}
				SHM_INTERP_START_CLR(rc_shm);
				SHM_INTERP_STATUS_CLR(rc_shm);
			}
			break;
		}
		case LIN: {
			PosSeq.clear();
			Position_ACS_rad oriPos = deg2rad(temp_inst.args[0].apv);
			std::cout << "InterpCompute oriPos " << temp_inst.args[0].apv.transpose() << std::endl;
			pInterpolator->LineInterp(oriPos,temp_inst.args[1].cpv,
											rc_core.Ts,500,100,100,0,0,rc_core.vper,PosSeq);
			if(!PosSeq.empty()){
				SHM_INTERP_STATUS_SET(rc_shm);
				SHM_INTERP_START_SET(rc_shm);
				while(!PosSeq.empty()){
					// std::cout << PosSeq.front().transpose() << std::endl;
					interp_step(PosSeq.front());
					PosSeq.pop_front();
				}
				SHM_INTERP_START_CLR(rc_shm);
				SHM_INTERP_STATUS_CLR(rc_shm);
			}
			break;
		}
		case CIRC:

			break;
		case JOINTJOG:{
			SHM_INTERP_STATUS_SET(rc_shm);
			SHM_INTERP_START_SET(rc_shm);
			double oriVel = 0;
			double oriAcc = 0;
			double oriJerk = 0;
			int count = 0;
			std::cout << "pos " << temp_inst.args[0].apv.transpose() << std::endl;
			do{	
				PosSeq.clear();
				pInterpolator->JointJogInterp(temp_inst.args[0].jjp.jointindex,
										  temp_inst.args[0].jjp.direction,
					                      temp_inst.args[0].apv, 
					                      oriVel, 
					                      oriAcc, 
					                      oriJerk, 
					                      rc_core.vper,
					                      rc_core.aper, 
					                      0, 
					                      2,
					                      rc_core.Ts, 
										  20, // N Ts inc incAcc 
										  rc_core.procedure, 
										  PosSeq);
				while(!PosSeq.empty()){
					// std::cout << PosSeq.front().transpose() << std::endl;
					interp_step(PosSeq.front());
					PosSeq.pop_front();
				}
				count ++;
				printf("**************************************%d*****************\n",count);

			} while(rc_core.jog_startup);
			rc_core.procedure = JOG_STOP;
			PosSeq.clear();
			pInterpolator->JointJogInterp(temp_inst.args[0].jjp.jointindex,
									  temp_inst.args[0].jjp.direction,
				                      temp_inst.args[0].apv, 
				                      oriVel, 
				                      oriAcc, 
				                      oriJerk, 
				                      rc_core.vper,
				                      rc_core.aper, 
				                      0, 
				                      2,
				                      rc_core.Ts, 
									  20, // N Ts inc incAcc 
									  rc_core.procedure, 
									  PosSeq);
			while(!PosSeq.empty()){
				// std::cout << PosSeq.front().transpose() << std::endl;
				interp_step(PosSeq.front());
				PosSeq.pop_front();
			}
			SHM_INTERP_START_CLR(rc_shm);
			SHM_INTERP_STATUS_CLR(rc_shm);
			break;
		}
		case CARTJOG: {
			SHM_INTERP_STATUS_SET(rc_shm);
			SHM_INTERP_START_SET(rc_shm);
			double Vellim[2] = {200,deg2rad(50)};  //
			double Acclim[2] = {80,deg2rad(80)};
			Position_ACS_rad oriPos = deg2rad(temp_inst.args[0].apv);
			double oriVel = 0;
			double oriAcc = 0;
			double oriJerk = 0;
			int count = 0;
			do{
				std::cout << "pos " << temp_inst.args[0].apv.transpose() << std::endl;
			 	PosSeq.clear(); 	
			 	pInterpolator->CartJogInterp(temp_inst.args[0].jjp.jointindex, 
										temp_inst.args[0].jjp.direction,
										oriPos,//deg2rad(temp_inst.args[0].apv),
										rc_core.coordinate,
										oriVel,oriAcc,oriJerk,
										rc_core.vper,0,0,
										2,
										Vellim, // mm/s ,
										Acclim,
				         				rc_core.Ts, 
				         				20,
				         				rc_core.procedure,
				         				PosSeq);
			 	while(!PosSeq.empty()){
					// std::cout << PosSeq.front().transpose() << std::endl;
					interp_step(PosSeq.front());
					PosSeq.pop_front();
				}
			 	count ++;
				printf("**************************************%d*****************\n",count);
			}while(rc_core.jog_startup);
			rc_core.procedure = JOG_STOP;
			PosSeq.clear();
		 	pInterpolator->CartJogInterp(temp_inst.args[0].jjp.jointindex, 
									temp_inst.args[0].jjp.direction,
									oriPos,//deg2rad(temp_inst.args[0].apv),
									rc_core.coordinate,
									oriVel,oriAcc,oriJerk,
									rc_core.vper,0,0,
									2,
									Vellim,// mm/s ,
									Acclim,
			         				rc_core.Ts, 
			         				20,
			         				rc_core.procedure,
			         				PosSeq);
		 	while(!PosSeq.empty()){
				// std::cout << PosSeq.front().transpose() << std::endl;
				interp_step(PosSeq.front());
				PosSeq.pop_front();
			}
			SHM_INTERP_START_CLR(rc_shm);
			SHM_INTERP_STATUS_CLR(rc_shm);
			break;
		}
		case AXIS_ADJUST: 
		{
			std::cout << "Come in AXIS_ADJUST" << std::endl;
			bool flag = false;
			send_cmd_to_rsi(1);
			do{
				// std::cout << "********** In RSI interp" << std::endl;
				bool lastPeriod = INRSIPeriod;
				/*
				PosSeq.clear();
				VelSeq.clear();
				if(!PosSeq.empty()){
					std::cout << "容器不空" << std::endl;
					std::cout << "original pos = " << PosSeq.front().transpose() << std::endl;
					std::cout << "original vel = " << VelSeq.front().transpose() << std::endl;
					temp_inst.args[0].apv = PosSeq.front();
				}
				// else {
				// 	// 这里测试时无法读取实际的角度，正式使用时需要修改　！！！
				// 	std::cout << "容器为空" << std::endl;
				// }
				RSI_AxisInterp(temp_inst.args[0].apv,
						   temp_inst.args[1].apv,
						   rc_core.Ts,
					   	   rc_core.vper*0.2,
					   	   rc_core.aper,
					       rc_runtime_param,
					       PosSeq,
					       VelSeq
						   );
				Posdatafile << "New Period " << std::endl;
				Veldatafile << "New Period " << std::endl; 
				PosUsedfile << "New Period " << std::endl;
				if(!RSIStopFlag && !PosSeq.empty() && flag && (lastPeriod ^ INRSIPeriod) == 0){
					SHM_INTERP_STATUS_SET(rc_shm);
					SHM_INTERP_START_SET(rc_shm);
					// rc_shm->interp_status = 1;
					// rc_shm->interp_startup_flag = 1;
					while(!RSIStopFlag && !PosSeq.empty() && flag && (lastPeriod ^ INRSIPeriod) == 0){
						// std::cout << PosSeq.front().transpose() << std::endl;
						PosUsedfile << PosSeq.front().transpose() << std::endl;
						interp_step(PosSeq.front());
						PosSeq.pop_front();
						VelSeq.pop_front();
					}
					SHM_INTERP_START_CLR(rc_shm);
					SHM_INTERP_STATUS_CLR(rc_shm);
					// rc_shm->interp_startup_flag = 0;
					// rc_shm->interp_status = 0;
				}	
				*/
				PosSeq.clear();
				Position_ACS_deg diff = (temp_inst.args[1].apv - temp_inst.args[0].apv)/5.0;
				for(int i = 1; i < 6; ++i){
					Position_ACS_deg tmp = temp_inst.args[0].apv + i*diff;
					PosSeq.push_back(tmp);
					// std::cout << tmp.transpose() << std::endl;
				}
				// std::cout << "******** interp points compute finish " << RSIStopFlag << std::endl;
				PosUsedfile << "New Period " << std::endl;
				if(!RSIStopFlag && flag && (lastPeriod^INRSIPeriod) == 0){
					SHM_INTERP_STATUS_SET(rc_shm);
					SHM_INTERP_START_SET(rc_shm);
					while(!RSIStopFlag && !PosSeq.empty() && flag && (lastPeriod^INRSIPeriod) == 0){
						PosUsedfile << PosSeq.front().transpose() << std::endl;
						interp_step(PosSeq.front());
						PosSeq.pop_front();
					}
					SHM_INTERP_START_CLR(rc_shm);
					SHM_INTERP_STATUS_CLR(rc_shm);
				}
				// std::cout << "************ RSI interp before read buffer " << RSIStopFlag << std::endl;
				while(!RSIStopFlag &&(lastPeriod ^ INRSIPeriod) == 0);
				// std::cout << "New RSI Period In Interpolator" << std::endl;
					// std::cout << "waiting RSI period" << std::endl;
				if(!RSIStopFlag)
					inst_buffer_read_nonblock(temp_inst, flag);
				// std::cout << "******************* flag = " << flag << std::endl;
			}while(flag && !RSIStopFlag);
			break;
		}
		case CART_ADJUST:
			break;
	}
}