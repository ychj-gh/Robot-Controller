#include "RobotModel.h"
#include <stdlib.h>

namespace RobotSpace{
	RobotModel::RobotModel(RobotConfig* rbtconf, std::shared_ptr<InverseKinInterface> pInvMtd)
		:_rbtName(rbtconf->name),_rbtType(rbtconf->robot_type),pInverseMethod(pInvMtd)
	{
		
		/* 配置文件中暂时没有对矩阵的配置，先用单位阵
		for(size_t i = 0; i < 4; ++i){
			for(size_t j = 0; j < 4; ++j){
				_toolMatrix(i,j) = rbtconf->toolMatrix[i][j];
				_baseMatrix(i,j) = rbtconf->baseMatrix[i][j];
			}
		}
		*/
		_toolMatrix = Identity4;
		_baseMatrix = Identity4;
		for(size_t i = 0; i < rbtconf->axis_count; ++i)
			_axes.push_back(std::make_shared<Axis>(rbtconf->axis[i]));
		if(!validateRobotType()){
			std::cerr << "Unmatched Robot Model!" << std::endl;
			exit(1);
		}
	}

	/**
	 *@brief  机器人正解,得到正解转换矩阵
	 */
	int RobotModel::calcForwardMatrix(const Position_ACS_rad& posACS, dmatrix& transMatrix) const
	{
		Position_ACS_rad q(posACS);
		dmatrix currentMatrix(_baseMatrix);

		for (std::vector<std::shared_ptr<Axis>>::size_type sz = 0; sz != _axes.size(); ++sz){
			if (_axes[sz]){
				_axes[sz]->_paramDH.theta = rad2deg(q(sz)) + _axes[sz]->_paramDH.offset;
				currentMatrix = currentMatrix * _axes[sz]->compute();
			}else{
				std::cerr<<"DH parameters can not be NULL." << std::endl;
				return -1;
			}
		}
		transMatrix = currentMatrix * _toolMatrix;
		return 0;
	}

	/**
	 *@brief  机器人正解,得到机器人末端RPY角(包括工具坐标系)
	 */
	int RobotModel::calcForwardKin_RPY(const Position_ACS_rad& posACS, Position_MCS_rad& posMCS) const/**< @note 弧度值*/
	{
		if(posACS.size() != _axes.size() || posMCS.size() != 6){
			std::cerr << "ForwardKin argument ERROR:";
			if(posACS.size() != _axes.size()) std::cerr << " posACS size = " << posACS.size() << std::endl;
			else std::cerr << "posMCS size = " << posMCS.size() << std::endl;
			return -1;
		}
		dmatrix transformationMatrix;
		calcForwardMatrix(posACS, transformationMatrix);
		posMCS << transformationMatrix.topRightCorner(3, 1),tr2rpy(transformationMatrix);
		return 0;
	}
}