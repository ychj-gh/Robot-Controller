/**
 *@brief 类 InterpolationInterface 插补基类 
 *  	 2017/12/10
 *  	 ychj
 */
#ifndef __INTERPOLATOR_INTERFACE_H__
#define __INTERPOLATOR_INTERFACE_H__
#include "RobotType.h"
#include "inst_type.h" // 后面修改
#include <deque>

namespace RobotSpace{
	class InterpolationInterface{
	public:
		InterpolationInterface(){}
		virtual ~InterpolationInterface(){}

	public:
		/*****************************************************************************/
		/**
	 	* @brief 关节插补 unit: deg
	 	* @param[in] originalPos 目标位置，角度 坐标系ACS
	 	* @param[in] targetPos 起始位置，角度 坐标系ACS 
	 	* @param[in] Ts 插补周期
	 	* @param[in] velPerc 速度百分比（0.5-95.0，例如：设定以50%的最大速度运行，赋值50）
	 	* @param[in] accPerc 加速度百分比（0.5-95.0）
	 	* @param[in] jerkPerc 加加速度百分比
	 	* @param[out] posSeq n组轴的位置插补（关节空间）序列，n为轴数
	 	* @return 若成功，返回 0
	 	* @attention 注意入口参数单位为角度
	 	*/
		/*****************************************************************************/
		virtual int JointInterp(const Position_ACS_deg& originalPos, const Position_ACS_deg& targetPos,double Ts,
				double velPerc, double accPerc, double jerkPerc, std::deque<Position_ACS_deg>& posSeq) = 0;
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
		virtual int LineInterp(const Position_ACS_rad& oriAxisPos, const Position_MCS_rad& tarPos,
					double Ts, double maxVel, double maxAcc,double maxDec,double maxJerk,
					double oriVel,double percVel,std::deque<Position_ACS_deg>& posSeq) = 0;
		// virtual int ArcInterp() = 0;
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
		virtual int JointJogInterp(size_t index, int direction, Position_ACS_deg& oriDeg,double& oriVel, 
			double& oriAcc,double& oriJerk,double velPerc,double accPerc,double jerkPerc,double incAcc,
			double Ts, size_t N, enum JogProc& procedure, std::deque<Position_ACS_deg>& posSeq) = 0;
		


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
		virtual int CartJogInterp(size_t index,int direction,Position_ACS_rad& oriAxisPos,int coor,
					double& oriVel,double& oriAcc,double& oriJerk,double velPerc,double decPerc,
					double jerkPerc,double incAcc,double *VelLim,double *AccLim,double Ts,
					size_t N,enum JogProc& procedure,std::deque<Position_ACS_deg>& posSeq) = 0;
	protected:
		//求系数a0,a1,a2...a5
		/**
	 	* @brief 求五次多项式的系数
	 	* @param 起始位置
	 	* @param 终止位置
	 	* @param 起始速度
	 	* @param 终止速度
	 	* @param 起始加速度
	 	* @param 终止加速度
	 	* @param 运行时间
	 	* @param 保存五次多项式系数的的结构体
	 	*/
		void getQuinticMultiCoe(double q0, double qf, double dq0, double dqf,
				double ddq0, double ddqf, double tf, dvector& coe5)
		{
			coe5[0]=q0;
			coe5[1]=dq0;
			coe5[2]=ddq0/2.0;
			coe5[3]=(20*qf-20*q0-(8*dqf+12*dq0)*tf-(3*ddq0-ddqf)*tf *tf)/(2*pow(tf, 3));
			coe5[4]=(30*q0-30*qf+(14*dqf+16*dq0)*tf+(3*ddq0-2*ddqf) *tf*tf)/(2 *pow(tf,4));
			coe5[5]=(12*qf-12*q0-(6*dq0+6*dqf)*tf-(ddq0-ddqf)*tf*tf) /(2*pow(tf, 5));
		}

		/**
	 	* @brief 五次多项式求解
	 	* @param x = r 
	 	* @param 五次多项式系数
	 	* @param 指向五次多项式的值的指针
	 	* @param 指向五次多项式一阶导的值的指针
	 	* @param 指向五次多项式二阶导的值的指针
	 	* @param 指向五次多项式三节导的值的指针
	 	*/
		void QuinticMultiPolynomi(double r, dvector& coe, double *qptr,
				double *dqptr/*=NULL*/, double *ddqptr/*=NULL*/, double *dddqptr/*=NULL*/)
		{
			if (qptr)
				*qptr = coe[0]+coe[1]*r+coe[2]*pow(r, 2)+coe[3]*pow(r, 3)+coe[4]*pow(r,
						4) +coe[5]*pow(r, 5);
			if (dqptr)
				*dqptr = coe[1]+2*coe[2]*r+3*coe[3]*pow(r, 2)+4*coe[4]*pow(r, 3)+5*coe[5] *pow(r, 4);
			if (ddqptr)
				*ddqptr = 2*coe[2]+6*coe[3]*r+12*coe[4]*pow(r, 2)+20*coe[5]*pow(r, 3);
			if (dddqptr)
				*dddqptr = 6*coe[3]+24*coe[4]*r+60*coe[5]*pow(r, 2);
		}

		void  getQuinticCoe(const double &start_deg, const double &end_deg, const double &start_vel, const double &end_vel,
					const double &start_acc, const double &end_acc, const double &tf, dvector &coe)
		{
			dmatrix A(6,6);
			dvector B(6);
			double t2 = tf * tf;
			double t3 = t2 * tf;
			double t4 = t3 * tf;
			double t5 = t4 * tf;
			B << start_deg, end_deg, start_vel, end_vel, start_acc, end_acc;
			A << 1,0,0,0,0,0,
				1,tf,t2,t3,t4,t5,
				0,1,0,0,0,0,
				0,1,2*tf,3*t2,4*t3,5*t4,
				0,0,2,0,0,0,
				0,0,2,6*tf,12*t2,20*t3;
			coe = A.lu().solve(B);	
		}

		void QuinticPolynomi(const double &t, const dvector &coe, double &ans)
		{
			double t2 = t * t;
			double t3 = t2 * t;
			double t4 = t3 * t;
			double t5 = t4 * t;
			ans = coe[0] + coe[1] * t + coe[2] * t2 + coe[3] * t3 + coe[4] * t4 + coe[5] * t5;
		}
	};
}
#endif