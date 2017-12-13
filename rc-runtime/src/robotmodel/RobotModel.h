/**
 *@brief 类RObotModel 
 *  	 2017/12/10
 *  	 ychj
 */
#ifndef __ROBOT_MODEL_H__
#define __ROBOT_MODEL_H__
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <native/mutex.h>

#include "../../../include/robotctl.h"
#include "Axis.h"
#include "RobotUtility.h"
#include "InverseKin.h"

namespace RobotSpace{
	class RobotModel{
	public:
		/**
 		 *  机器人模型构造函数
		 */
		RobotModel(RobotConfig* rbtconf, std::shared_ptr<InverseKinInterface> pInvMtd = std::make_shared<InverseNormal>());
		RobotModel(std::vector<std::shared_ptr<Axis>>& axisVec,const std::string& nm = std::string(""), 
			std::shared_ptr<InverseKinInterface> pInvMtd = std::make_shared<InverseNormal>(), ROBOT_TYPE tp = GENERAL_RBT_TYPE,
			const Matrix4d& tmat = Identity4,const Matrix4d& bmat = Identity4)
		:_axes(axisVec),_rbtName(nm),pInverseMethod(pInvMtd),_rbtType(tp),_toolMatrix(tmat),_baseMatrix(bmat){}
		~RobotModel(){}
	public:
		/**
 		 *  机器人名
		 */
		std::string getRobotName() const {
			return _rbtName;
		}
		/**
 		 *@brief  机器人轴数
		 */
		size_t getRobotAxisNum() const {
			return _axes.size();
		}

		/**
 		 *@brief  获得机器人极限参数
		 */
		std::vector<Lim_param> getLimParameters() const{
			std::vector<Lim_param> ret;
			for(size_t i = 0; i != _axes.size(); ++i)
				ret.push_back(_axes[i]->_paramLim);
			return ret;
		}
		/**
		 *@brief  提供设置工具坐标系接口　后面需要验证toolmat正确性
		 */
		int setToolMatrix(const Matrix4d& toolmat){
			_toolMatrix = toolmat;
			return 0;
		}

		int setToolMatrix(const Position_MCS_rad& posTool){
			_toolMatrix = rpy2tr(posTool);
			return 0;
		}

		/**
		 *@brief  提供设置工具坐标系接口　后面需要验证toolmat正确性
		 */
		int setInverseKinMethod(std::shared_ptr<InverseKinInterface>& pMethod){
			if(pMethod)		pInverseMethod = pMethod;
			return 0;
		}
		/**
		 *@brief  打印机器人信息
		 */
		void PrintInformation(std::ostream& os){
			os << "机器人名称：\t" <<  _rbtName << " " << _axes.size() << std::endl;
			os << "机器人类型：\t";
			switch(_rbtType){
				case GENERAL_RBT_TYPE: os << "普通六轴机器人" << std::endl;
					break;
				case OTHERS: os << "其他" << std::endl;
					break;
				default:
					break;
			}
			// os << "参考坐标系：\t" << (_coorSys == 1 ? "直角坐标系":"关节坐标系") << std::endl;
			os << "\t机器人参数" << std::endl;
			os << "DH参数：" << std::endl;
			os << "alpha\ta\ttheta\td\toffset" << std::endl;
			for(std::vector<std::shared_ptr<Axis>>::size_type i = 0; i != _axes.size(); ++i)
				os << _axes[i]->_paramDH.alpha << "\t" << _axes[i]->_paramDH.a << "\t"<< _axes[i]->_paramDH.theta << "\t" 
				<< _axes[i]->_paramDH.d << "\t" << _axes[i]->_paramDH.offset << std::endl;
			os << "极限参数: " << std::endl;
			os << "+Pos\t" << "-Pos\t" << "maxVel\t" << "maxAcc\t" << "maxDec\t" << "maxJerk" << std::endl;
			for(std::vector<std::shared_ptr<Axis>>::size_type i = 0; i != _axes.size(); ++i)
				os << _axes[i]->_paramLim.max_pos << "\t" << _axes[i]->_paramLim.min_pos << "\t"
					<< _axes[i]->_paramLim.max_vel << "\t" << _axes[i]->_paramLim.max_acc << "\t" 
					<< _axes[i]->_paramLim.max_dec << "\t" << _axes[i]->_paramLim.max_jerk << std::endl;
		}

	public:
		/**
		 *@brief  根据电机实际角度获取在机器人系统下各轴的角度值(deg)
	 	*/		
		int getActualAxisPos(RCMem* shm, RT_MUTEX* mutex,std::vector<double>& pos) 
		{
	    	rt_mutex_acquire(mutex, TM_INFINITE);
	    	for(size_t i = 0; i != _axes.size(); ++i){ 
	       	  _axes[i]->_actualDeg = shm->data.axis_info[i].actual_pos;
	    	  pos[i] = _axes[i]->motor2RobotPos();
	    	}
	   	 	rt_mutex_release(mutex);
			return 0;
		}
		/**
		 *@brief  根据电机实际角度获取在机器人系统下各轴的角度值(deg)
	 	*/		
		int getActualAxisPos(RCMem* shm, RT_MUTEX* mutex,Position_ACS_deg& pos) 
		{
	    	rt_mutex_acquire(mutex, TM_INFINITE);
	    	for(size_t i = 0; i != _axes.size(); ++i){ 
	       	  _axes[i]->_actualDeg = shm->data.axis_info[i].actual_pos;
	    	  pos[i] = _axes[i]->motor2RobotPos();
	    	}
	   	 	rt_mutex_release(mutex);
			return 0;
		}
		/**
		 *@breif 由于Estun机器人伺服系统偏差较大，可能需要将上一次的控制量作为这一次的初始位置
		 */
		int getCommandAxisPos(RCMem* shm, RT_MUTEX* mutex, Position_ACS_deg& pos)
		{
			rt_mutex_acquire(mutex,TM_INFINITE);
			for(size_t i = 0; i != _axes.size(); ++i)
				pos[i] = _axes[i]->motor2RobotPos(shm->data.interp_value[i].command_pos);
			rt_mutex_release(mutex);
			return 0;
		}
		/**
		 *@brief  根据电机实际角度获取在机器人系统下的机器人末端的位姿(mm/rad)
	 	*/			
		int getActualTCPPos(RCMem* shm, RT_MUTEX* mutex,Position_MCS_rad& pos)
		{
			if(pos.size() != 6) return -1;
			Position_ACS_deg deg;
			getActualAxisPos(shm,mutex,deg);
			calcForwardKin_RPY(deg2rad(deg),pos);
			return 0;
		}
		/**
		 *@brief  获取在机器人系统下的各关节角和机器人末端的位姿(mm deg)
	 	*/	
		int getActualPoses(RCMem* shm, RT_MUTEX* mutex,Position_ACS_deg& posA, Position_MCS_deg& posT)
		{
			if(posT.size() != 6) return -1;
			getActualAxisPos(shm,mutex,posA);
			Position_MCS_rad pos(6);
			calcForwardKin_RPY(deg2rad(posA),pos);
			posT = rad2deg(pos);
			return 0;
		}
		/**
		 *@brief  将机器人系统下的角度转换为电机实际角度值，并写入共享内存
	 	*/	
		int setMotorAxisPos(RCMem* shm, RT_MUTEX* mutex, Position_ACS_deg& pos){
			rt_mutex_acquire(mutex,TM_INFINITE);
			for(size_t i = 0; i != pos.size(); ++i)
				shm->data.interp_value[i].command_pos = _axes[i]->robot2MotorPos(pos(i));
			rt_mutex_release(mutex);
			return 0;
		}

	public:
		/**
		 *@brief  机器人正解,得到正解转换矩阵(包括工具坐标系)
	 	*/
		int calcForwardMatrix(const Position_ACS_rad& posACS, dmatrix& transMatrix) const;
		/**
		 *@brief  机器人正解,得到机器人末端RPY角(包括工具坐标系)
		 */
		int calcForwardKin_RPY(const Position_ACS_rad& posACS, Position_MCS_rad& posMCS) const; /**< @note 弧度值*/
		
		/**
 		 *@brief  机器人逆解(使用策略模式实现不同结构的机器人采用不同的逆解算法)
		 */
		int calcInverseKin_Trans(const dmatrix& transMatrix,
			const Position_ACS_rad& posLast, Position_ACS_rad& posACS) const//< @note 弧度值/
		{
			// std::cout << "calcInverseKin_Trans" << std::endl;
			if(transMatrix.rows() != 4 || transMatrix.cols() != 4){
				std::cerr << "calcInverseKin_Trans argument ERROR" << std::endl;
				return -1;
			}
			return pInverseMethod->calcInverseKin(_axes,_baseMatrix,_toolMatrix,transMatrix,posLast,posACS);
		} 
		/**
 		 *@brief  机器人逆解(给出末端RPY角计算关节角)
		 */
		int calcInverseKin_RPY(const Position_MCS_rad& posMCS,
		 	const Position_ACS_rad& posLast, Position_ACS_rad& posACS) const
		{	
			// std::cout << "calcInverseKin_RPY" << std::endl;
			if(posMCS.size() != 6){
				std::cerr << "calcInverseKin_RPY argument ERROR" << std::endl;
				return -1;
			}
			dmatrix T(4,4);
			T = rpy2tr(posMCS);
			return calcInverseKin_Trans(T,posLast,posACS);
		}

		/**
		 *@breif 机器人工具坐标系下位姿转换为世界坐标系下位姿
		 */ 
		int toolRPY2baseRPY(const Position_ACS_rad& axisPos, 
			const Position_MCS_rad& toolPos, Position_MCS_rad& basePos) const
		{	
			dmatrix transMatrix(4,4);
			calcForwardMatrix(axisPos,transMatrix);
			transMatrix = transMatrix * rpy2tr(toolPos);
			basePos = tr2MCS(transMatrix);
			return 0;
		}

		/**
		 *@breief
		 */
		int toolRPY2axisPos(const Position_MCS_rad& axisPos,
			const Position_ACS_rad& toolPos, Position_ACS_rad& outPos) const
		{
			dmatrix transMatrix(4,4);
			calcForwardMatrix(axisPos,transMatrix);
			transMatrix = transMatrix * rpy2tr(toolPos);
			calcInverseKin_Trans(transMatrix,axisPos,outPos);
			return 0;
		}
	private:
		/**
		 *@brief 根据_axes简单验证机器人模型是否符合设置的type
		 */
		bool validateRobotType(){
			return _rbtType == GENERAL_RBT_TYPE && _axes.size() == 6 ||
				   _rbtType == OTHERS;
		}
	private:
		std::string _rbtName;
		ROBOT_TYPE  _rbtType;
		// COORD_SYS	_coorSys;
		std::vector<std::shared_ptr<Axis>> _axes;
		Matrix4d _toolMatrix;
		Matrix4d _baseMatrix;
		std::shared_ptr<InverseKinInterface> pInverseMethod;
	};
}

#endif