/**
 *@brief 类 InterpolationDefault 默认插补类点动实现
 *  	 2017/12/11
 *  	 ychj
 */
#include "InterpolationDefault.h"

namespace RobotSpace{
	/*****************************************************************************/
	/**
 	* @brief 单轴关节点动插补 unit: deg
 	* @param[in] index  点动轴下标
 	* @param[in] direction 点动运动方向　0:负方向　其他:正方向
 	* @param[in] oriDeg 起始位置，角度 坐标系ACS
 	* @param[in] oriVel 起始速度　(deg/s)
 	* @param[in] oriAcc 起始加速度 (deg/s^2)
 	* @param[in] oriJerk 起始加加速度
 	* @param[in] velPerc 点动最大速度占极限速度的百分比　如20,30
 	* @param[in] accPerc 点动最大加速度百分比
 	* @param[in] jerkPerc 点动最大加加速度百分比
 	* @param[in] incAcc  变加速段每 Ts*N 时间内增加的加速度
 	* @param[in] Ts 插补周期
 	* @param[in] N  N个插补周期为一个点动周期
 	* @param[in] procdure 点动进入的阶段(变加速段，匀速段，停止段)
 	* @param[out] posSeq n个轴的位置插补（关节空间）序列，n为轴数 deg
 	* @return 若成功，返回 0
 	* @attention 注意入口参数单位为角度  
 	*	除停止段每 Ts * N 个周期计算一次，即每个计算周期插补点个数为 N；
 	*   判断进入哪个阶段(刚运行时进入变加速阶段，匀速段会自动进入，	 		
 	*	当收到停止信号，将procedure 手动置为 STOP)
 	*/
	/*****************************************************************************/
	int InterpolationDefault::JointJogInterp(size_t index, int direction, Position_ACS_deg& oriDeg,
			double& oriVel, double& oriAcc, double& oriJerk, double velPerc, double accPerc, double jerkPerc,
			double incAcc, double Ts, size_t N, enum JogProc& procedure, std::deque<Position_ACS_deg>& posSeq)
	{
		double tN = Ts * N;
		if(direction == 0) direction = -1;
		else direction = 1;
		double maxVel = direction * velPerc / 100.0 * paramLim[index].max_vel;
		double maxAcc = direction * accPerc / 100.0 * paramLim[index].max_acc;
		size_t n = pRobot->getRobotAxisNum();
		incAcc = direction * incAcc;
		switch(procedure)
		{
			case JOG_INCONSTACC:
			{
				double acc = oriAcc + incAcc;
				if(direction > 0 && acc > maxAcc)  acc = maxAcc;
				else if(direction < 0 && acc < maxAcc) acc = maxAcc;
				double a0 = oriDeg[index];
				double a1 = oriVel;
				double a3 = 2 * acc / (3 * tN);
				double a4 = - acc / (3 * tN * tN);
				double Vtmp = a1 + 3 * a3 * tN * tN + 4 * a4 * tN * tN * tN;
				if(fabs(Vtmp) <= fabs(maxVel))
				{
					for(size_t i = 0; i < N; ++ i)
					{
						double t = i * Ts;
						Position_ACS_deg tmp(n);
						tmp[index] = a0 + a1 * t + a3 * t * t * t + a4 * t * t * t * t;
						if(direction > 0 && tmp[index] > paramLim[index].max_pos)
							tmp[index] = paramLim[index].max_pos;
						else if(direction < 0 && tmp[index] < paramLim[index].min_pos)
							tmp[index] = paramLim[index].min_pos;
						for(size_t ai = 0; ai != n; ++ai)
							if(ai != index) tmp[ai] = oriDeg[ai];
						posSeq.push_back(tmp);
						// interp_step(tmp);
					}
					double Ptmp = a0 + a1 * tN + a3 * tN * tN * tN + a4 * tN * tN * tN * tN;
					oriDeg[index] = Ptmp;
					oriVel = Vtmp;
					oriAcc = acc;
				}	
				else
				{
					double a3 = (maxVel - oriVel) / (tN * tN);
					double a4 = (oriVel - maxVel) / (2 * tN * tN * tN);
					for(size_t i =0; i < N; ++i)
					{
						double t = i * Ts;
						Position_ACS_deg tmp(n);
						tmp[index] = a0 + a1 * t + a3 * t * t * t + a4 * t * t * t * t;
						if(direction > 0 && tmp[index] > paramLim[index].max_pos)
							tmp[index] = paramLim[index].max_pos;
						else if(direction < 0 && tmp[index] < paramLim[index].min_pos)
							tmp[index] = paramLim[index].min_pos;
						for(size_t ai = 0; ai != n; ++ai)
							if(ai != index) tmp[ai] = oriDeg[ai];
						posSeq.push_back(tmp);
						// interp_step(tmp);
					}
					double Ptmp = a0 + a1 * tN + a3 * tN * tN * tN + a4 * tN * tN * tN * tN;
					oriDeg[index] = Ptmp;
					oriVel = maxVel;
					oriAcc = 0;
					procedure = JOG_CONSTVEL;
				}
				break;
			}
			case JOG_CONSTVEL:
			{
				for(size_t i =0; i < N; ++i)
				{
					double t = i * Ts;
					Position_ACS_deg tmp(n);
					tmp[index] = oriDeg[index] + maxVel * t;
					if(direction > 0 && tmp[index] > paramLim[index].max_pos)
						tmp[index] = paramLim[index].max_pos;
					else if(direction < 0 && tmp[index] < paramLim[index].min_pos)
						tmp[index] = paramLim[index].min_pos;
					for(size_t ai = 0; ai != n; ++ai)
						if(ai != index) tmp[ai] = oriDeg[ai];
					posSeq.push_back(tmp);
					// interp_step(tmp);
				}	
				double Ptmp = oriDeg[index] + maxVel * tN;
				oriDeg[index] = Ptmp;
				oriVel = maxVel;
				break;
			}
			case JOG_STOP:
			{
				double a0 = oriDeg[index];
				double a1 = oriVel;
				maxAcc = 5 * maxAcc;
				double a3 = -4 * maxAcc * maxAcc / (9 * oriVel);
				double a4 = 4 * maxAcc * maxAcc * maxAcc / (27 * oriVel * oriVel);
				double deltaT = 3 * oriVel / (2 * maxAcc);
				size_t N2 = deltaT / Ts;
				Position_ACS_deg tmp(n);
				for(size_t i = 0; i < N2; ++i)
				{	
					double t = i * Ts;
					tmp[index] = a0 + a1 * t + a3 * t * t * t + a4 * t * t * t * t;
					if(direction > 0 && tmp[index] > paramLim[index].max_pos)
						tmp[index] = paramLim[index].max_pos;
					else if(direction < 0 && tmp[index] < paramLim[index].min_pos)
						tmp[index] = paramLim[index].min_pos;
					for(size_t ai = 0; ai != n; ++ai)
						if(ai != index) tmp[ai] = oriDeg[ai];
					posSeq.push_back(tmp);
					// interp_step(tmp);
				}
				tmp[index] = a0 + a1 * deltaT + a3 * deltaT * deltaT * deltaT + a4 * deltaT * deltaT * deltaT * deltaT;
				if(direction > 0 && tmp[index] > paramLim[index].max_pos)
					tmp[index] = paramLim[index].max_pos;
				else if(direction < 0 && tmp[index] < paramLim[index].min_pos)
					tmp[index] = paramLim[index].min_pos;
				for(size_t ai = 0; ai != n; ++ai)
					if(ai != index) tmp[ai] = oriDeg[ai];
				posSeq.push_back(tmp);
				// interp_step(tmp);
				oriDeg[index] = tmp[index];
				oriVel = 0;
				oriAcc = 0;
				break;
			}
		}
		return 0;
	}


	/*****************************************************************************/
	/**
 	* @brief　直角坐标系下点动插补 unit: rad mm
 	* @param[in] index  点动轴下标
 	* @param[in] direction 点动运动方向　0:负方向　其他:正方向
 	* @param[in] oriAxisPos 起始位置，角度 坐标系ACS
 	* @param[in] coor  坐标系,基坐标系下点动｜工具坐标系下点动
 	* @param[in] oriVel 起始速度　(mm/s | rad/s)
 	* @param[in] oriAcc 起始加速度 (mm/s^2 | rad/s^2)
 	* @param[in] oriJerk 起始加加速度
 	* @param[in] velPerc 点动最大速度占极限速度的百分比　如20,30
 	* @param[in] accPerc 点动最大加速度百分比
 	* @param[in] jerkPerc 点动最大加加速度百分比
 	* @param[in] incAcc  变加速段每 Ts*N 时间内增加的加速度
 	* @param[in] VelLim  二维速度极限数组[(x,y,z),(a,b,c)] (mm/s,rad/s)
 	* @param[in] AccLim  二维加速度极限数组(mm/s^2,rad/s^2) 
 	* @param[in] Ts 插补周期
 	* @param[in] N  N个插补周期为一个点动周期
 	* @param[in] procdure 点动进入的阶段(变加速段，匀速段，停止段)
 	* @param[out] posSeq n个轴的位置插补（关节空间）序列，n为轴数 deg
 	* @return 若成功，返回 0
 	* @attention 注意入口参数单位为角度  
 	*	除停止段每 Ts * N 个周期计算一次，即每个计算周期插补点个数为 N；
 	*   判断进入哪个阶段(刚运行时进入变加速阶段，匀速段会自动进入，	 		
 	*	当收到停止信号，将procedure 手动置为 STOP)
 	*/
	/*****************************************************************************/
	int InterpolationDefault::CartJogInterp(size_t index,int direction,Position_ACS_rad& oriAxisPos,
				int coor,double& oriVel,double& oriAcc,double& oriJerk,double velPerc,
				double decPerc,double jerkPerc,double incAcc,double *VelLim,double *AccLim,
				double Ts,size_t N,enum JogProc& procedure,std::deque<Position_ACS_deg>& posSeq)
	{
		std::cout << "Start CartJogInterp " << std::endl;
		double tN = Ts * N;
		if(direction == 0)	direction = -1;
		else 				direction = 1;
		size_t n = pRobot->getRobotAxisNum();
		double maxVel, maxAcc;
		if(index < 3)
		{
			 maxVel = direction * velPerc / 100.0 * VelLim[0];
			 maxAcc = direction * AccLim[0];
		}
		else 
		{
			maxVel = direction * velPerc / 100.0 * VelLim[1];
			maxAcc = direction * AccLim[1];
		}
		incAcc = direction * incAcc;
		dmatrix transT(4,4);
		if(pRobot->calcForwardMatrix(oriAxisPos,transT) != 0)
			return -1;
		// std::cout << "check point 1" << std::endl;
		Position_ACS_rad last_tmp(oriAxisPos);
		Position_ACS_rad tmp(n);
		Position_MCS_rad OutPos(6);
		switch(procedure)
		{
			case JOG_INCONSTACC:
			{
				double acc = oriAcc + incAcc;
				if(fabs(acc) > fabs(maxAcc))  acc = maxAcc;
				double a1 = oriVel;
				double a3 = 2 * acc / (3 * tN);
				double a4 = - acc / (3 * tN * tN);
				double Vtmp = a1 + 3 * a3 * tN * tN + 4 * a4 * tN * tN * tN;
				if(fabs(Vtmp) <= fabs(maxVel))
				{
					for(size_t i = 0; i < N; ++ i)
					{
						double t = i * Ts;
						Position_MCS_rad Ttmp(6);
						dmatrix 	transTtmp(4,4);
						Ttmp[index] = a1 * t + a3 * t * t * t + a4 * t * t * t * t;
						for(size_t ai = 0; ai != 6; ++ai)
							if(ai != index) Ttmp[ai] = 0;
						dmatrix deltaT = rpy2tr(Ttmp);
						if(coor == BASE)  		transTtmp = deltaT * transT;
						else if(coor == TOOL)		transTtmp = transT * deltaT;
						// std::cout << "check point 2" << std::endl;
						if(pRobot->calcInverseKin_Trans(transTtmp,last_tmp, tmp) == -1)
						{
							tmp = last_tmp;
							std::cout << " Can't move to target !" << std::endl;
							break;
						}
						/* for test */
						pRobot->calcForwardKin_RPY(tmp,OutPos);		
						std::cout << "Pos = " << OutPos.transpose() << std::endl;
						last_tmp = tmp;
						posSeq.push_back(rad2deg(tmp));
						// interp_step(tmp);
					}
					// std::cout << "check point 3" << std::endl;
					oriAxisPos = tmp;
					oriVel = Vtmp;
					oriAcc = acc;
				}
				else
				{
					double a3 = (maxVel - oriVel) / (tN * tN);
					double a4 = (oriVel - maxVel) / (2 * tN * tN * tN);
					for(size_t i =0; i < N; ++i)
					{
						double t = i * Ts;
						Position_MCS_rad Ttmp(6);
						dmatrix 	transTtmp(4,4);
						Ttmp[index] = a1 * t + a3 * t * t * t + a4 * t * t * t * t;
						for(size_t ai = 0; ai != 6; ++ai)
							if(ai != index) Ttmp[ai] = 0;
						dmatrix deltaT = rpy2tr(Ttmp);
						if(coor == BASE)  			transTtmp = deltaT * transT;
						else if(coor == TOOL)		transTtmp = transT * deltaT;
						// std::cout << "check point 4" << std::endl;
						if(pRobot->calcInverseKin_Trans(transTtmp,last_tmp,tmp) == -1)
						{
							tmp = last_tmp;
							std::cout << " Can't move to target !" << std::endl;
							std::cout << " Last_tmp = " << last_tmp.transpose() << std::endl;
							break;
						}
						/* for test */
						pRobot->calcForwardKin_RPY(tmp,OutPos);		
						std::cout << "Pos = " << OutPos.transpose() << std::endl;
						last_tmp = tmp;
						posSeq.push_back(rad2deg(tmp));
						// interp_step(tmp);
					}
					// std::cout << "check point 5" << std::endl;
					oriAxisPos = tmp;
					oriVel = maxVel;
					oriAcc = 0;
					procedure = JOG_CONSTVEL;
				}
				break;	
			}
			case JOG_CONSTVEL:
			{
				for(size_t i =0; i < N; ++i)
				{
					double t = i * Ts;
					Position_MCS_rad Ttmp(6);
					dmatrix transTtmp(4,4);
					Ttmp[index] = maxVel * t;
					for(size_t ai = 0; ai != 6; ++ai)
						if(ai != index) Ttmp[ai] = 0;
					dmatrix deltaT = rpy2tr(Ttmp);
					if(coor == BASE)  		transTtmp = deltaT * transT;
					else if(coor == TOOL)		transTtmp = transT * deltaT;
					if(pRobot->calcInverseKin_Trans(transTtmp,last_tmp,tmp) == -1)
					{
						tmp = last_tmp;
						std::cout << " Can't move to target !" << std::endl;
						std::cout << " Last_tmp = " << last_tmp.transpose() << std::endl;
						break;
					}
					/* for test */
					pRobot->calcForwardKin_RPY(tmp,OutPos);		
					std::cout << "Pos = " << OutPos.transpose() << std::endl;
					last_tmp = tmp;
					posSeq.push_back(rad2deg(tmp));
					// interp_step(tmp);
				}	
				oriAxisPos = tmp;
				oriVel = maxVel;
				break;
			}
			case JOG_STOP:
			{
				double a1 = oriVel;
				double a3 = -4 * maxAcc * maxAcc / (9 * oriVel);
				double a4 = 4 * maxAcc * maxAcc * maxAcc / (27 * oriVel * oriVel);
				double deltaTime = 3 * oriVel / (2 * maxAcc);
				size_t N2 = deltaTime / Ts;
				Position_MCS_rad Ttmp(6);
				dmatrix transTtmp(4,4);
				for(size_t i = 0; i < N2; ++i)
				{	
					double t = i * Ts;
					Ttmp[index] = a1 * t + a3 * t * t * t + a4 * t * t * t * t;
					for(size_t ai = 0; ai != 6; ++ai)
						if(ai != index) Ttmp[ai] = 0;
					dmatrix deltaT = rpy2tr(Ttmp);
					if(coor == BASE)  			transTtmp = deltaT * transT;
					else if(coor == TOOL)		transTtmp = transT * deltaT;
					if(pRobot->calcInverseKin_Trans(transTtmp,last_tmp,tmp) == -1)
					{
						tmp = last_tmp;
						std::cout << " Can't move to target !" << std::endl;
						std::cout << " Last_tmp = " << last_tmp.transpose() << std::endl;
						break;
					}
					/* for test */
					pRobot->calcForwardKin_RPY(tmp,OutPos);		
					std::cout << "Pos = " << OutPos.transpose() << std::endl;
					last_tmp = tmp;
					posSeq.push_back(rad2deg(tmp));
					// interp_step(tmp);
				}
				Ttmp[index] = a1 * deltaTime + a3 * deltaTime * deltaTime * deltaTime + a4 * deltaTime * deltaTime * deltaTime * deltaTime;
				for(size_t ai = 0; ai != n; ++ai)
					if(ai != index) Ttmp[ai] = 0;
				dmatrix deltaT = rpy2tr(Ttmp);
				if(coor == BASE)  			transTtmp = deltaT * transT;
				else if(coor == TOOL)		transTtmp = transT * deltaT;
				if(pRobot->calcInverseKin_Trans(transTtmp,last_tmp,tmp) == -1)
				{
					tmp = last_tmp;
					std::cout << " Can't move to target !" << std::endl;
					std::cout << " Last_tmp = " << last_tmp.transpose() << std::endl;
					break;
				}
				/* for test */
				pRobot->calcForwardKin_RPY(tmp,OutPos);		
				std::cout << "Pos = " << OutPos.transpose() << std::endl;
				last_tmp = tmp;
				posSeq.push_back(rad2deg(tmp));
				// interp_step(tmp);
				oriAxisPos = tmp;
				oriVel = 0;
				oriAcc = 0;
				break;
			}
		}
	}

}