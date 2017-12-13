/**
 *@brief 类 InterpolationDefault 默认插补类
 *  	 2017/12/10
 *  	 ychj
 */
#ifndef __INTERPOLATIONDEFAULT_H__
#define __INTERPOLATIONDEFAULT_H__
#include "InterpolationInterface.h"
#include "RobotModel.h"
#include "../../../include/robotctl.h"
#include <memory>
#include <vector>
#include <iostream>

namespace RobotSpace{
	class InterpolationDefault:public InterpolationInterface{
	public:
		InterpolationDefault(RobotModel* pRbt/*const std::shared_ptr<RobotModel>& pRbt*/):
						pRobot(pRbt)
		{ 
			paramLim = pRobot->getLimParameters();
		}
		~InterpolationDefault(){}

		/* just for debug */
		void Print(std::ostream& os = std::cout){
			os << "-Pos\t+Pos\tmaxVel\tmaxAcc\tmaxDec\tmaxJerk" << std::endl;
			for(size_t i = 0; i != paramLim.size(); ++i){
				os << paramLim[i].min_pos << "\t" << paramLim[i].max_pos << "\t" << paramLim[i].max_vel
				<< "\t" << paramLim[i].max_acc << "\t"<<paramLim[i].max_dec << "\t"<<paramLim[i].max_jerk<< std::endl;
			}
		}
	public:
		/*****************************************************************************/
		/**
	 	* @brief 关节插补 unit: deg
	 	* @param[in] originalPos 起始位置，角度 坐标系ACS
	 	* @param[in] targetPos 目标位置，角度 坐标系ACS 
	 	* @param[in] Ts 插补周期
	 	* @param[in] velPerc 速度百分比（0.5-95.0，例如：设定以50%的最大速度运行，赋值50）
	 	* @param[in] accPerc 加速度百分比（0.5-95.0）
	 	* @param[in] jerkPerc 加加速度百分比
	 	* @param[out] posSeq n组轴的位置插补（关节空间）序列，n为轴数
	 	* @return 若成功，返回 0
	 	* @attention 注意入口参数单位为角度
	 	*/
		/*****************************************************************************/
		int JointInterp(const Position_ACS_deg& originalPos, const Position_ACS_deg& targetPos,double Ts,
								double velPerc,double accPerc ,double jerkPerc ,std::deque<Position_ACS_deg>& posSeq); 
		
		/*****************************************************************************/
		/**
		 * @brief 位置控制模式下，笛卡尔坐标系下按直线插补
		 * @param[in] oriAxisPos 起始位置(ACS)， 弧度(关节) 
		 * @param[in] tarPos 目标位置，弧度(机器人末端)
		 * @param[in] Ts 插补周期
		 * @param[in] maxVel 最大速度(机器人末端)
		 * @param[in] maxAcc 最大加速度(机器人末端)
		 * @param[in] maxDec 最大减速度(机器人末端)
		 * @param[in] maxJerk 最大加加速度(机器人末端)
		 * @param[in] oriVel 起始速度(机器人末端)
		 * @param[in] percVel 　速度百分比
		 * @param[out] posSeq n组轴的位置插补（关节空间）序列，n为轴数
		 * @return 若成功，返回 0
		 * @attention 注意入口参数单位为弧度
		 * @todo 角速度限制
		 */
		/*****************************************************************************/
		int LineInterp(const Position_ACS_rad& oriAxisPos, const Position_MCS_rad& tarPos,
					double Ts, double maxVel, double maxAcc,double maxDec,double maxJerk,
					double oriVel,double percVel,std::deque<Position_ACS_deg>& posSeq);

	public:
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
	 	* @param[out] posSeq n个轴的位置插补（关节空间）序列，n为轴数
	 	* @return 若成功，返回 0
	 	* @attention 注意入口参数单位为角度  
	 	*	除停止段每 Ts * N 个周期计算一次，即每个计算周期插补点个数为 N；
	 	*   判断进入哪个阶段(刚运行时进入变加速阶段，匀速段会自动进入，	 		
	 	*	当收到停止信号，将procedure 手动置为 STOP)
	 	*/
		/*****************************************************************************/
		int JointJogInterp(size_t index, int direction, Position_ACS_deg& oriDeg,double& oriVel, 
			double& oriAcc,double& oriJerk,double velPerc,double accPerc,double jerkPerc,double incAcc,
			double Ts, size_t N, enum JogProc& procedure, std::deque<Position_ACS_deg>& posSeq);
	
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
		int CartJogInterp(size_t index,int direction,Position_ACS_rad& oriAxisPos,int coor,
					double& oriVel,double& oriAcc,double& oriJerk,double velPerc,double decPerc,
					double jerkPerc,double incAcc,double *VelLim,double *AccLim,double Ts,
					size_t N,enum JogProc& procedure,std::deque<Position_ACS_deg>& posSeq);

	private:
		std::vector<Lim_param>  paramLim;
		RobotModel* pRobot;
		// std::shared_ptr<RobotModel>  pRobot;
	};
}


#endif