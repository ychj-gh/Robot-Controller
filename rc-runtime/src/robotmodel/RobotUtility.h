#ifndef __ROBOT_UTILITY_H__
#define __ROBOT_UTILITY_H__

#include "RobotType.h"

#define rad2deg(r)   	((r)*180.0/M_PI)
#define deg2rad(d) 		((d)*M_PI/180.0)

namespace RobotSpace{
	/**
	 *@brief RPY求解,x,y,z in order,单位为弧度？？？？？？？
	 */
	//x,y,z order, 弧度
	inline RPY tr2rpy(dmatrix m)
	{
		RPY rpy;
		/*
			rpy(0) = atan2(-m(1, 2), m(2, 2)); // a = atan2(-Oy, Oz)
			double sr = sin(rpy(0, 0)); //sina
			double cr = cos(rpy(0, 0)); //cosa
			rpy(1) = atan2(m(0, 2), cr*m(2, 2)-sr*m(1, 2)); //atan2(
			rpy(2) = atan2(-m(0, 1), m(0, 0));
		*/
		//rpy(0) = atan2(m(2,1),m(2,2));
		rpy(0) = atan2((double)m(2,1),(double)m(2,2));
		rpy(1) = atan2(-1.0*(double)m(2,0),(double)sqrt((double)pow((double)m(0,0),2.0)+(double)pow((double)m(1,0),2.0)));
		rpy(2) = atan2((double)m(1,0),(double)m(0,0));
		return rpy;
	}
	/**
	 *@brief return 返回位移和RPY角度（用弧度表示）
	 */
	//x,y,z order
	inline Position_MCS_rad tr2MCS(dmatrix m)
	{
		Position_MCS_rad posMCS(6);
		posMCS << m.block(0, 3, 3, 1), tr2rpy(m);
		return posMCS;
	}
	/**
	 *@brief 根据RPY转换为旋转矩阵
	 *@return 旋转矩阵(3*3)
	 */
	//x,y,z order
	inline dmatrix rpy2r(RPY rpy)
	{
	/*
		return Eigen::AngleAxisd(rpy(0), Vector3::UnitX()).toRotationMatrix() * Eigen::AngleAxisd(rpy(1), Vector3::UnitY()).toRotationMatrix() * Eigen::AngleAxisd(rpy(2), Vector3::UnitZ()).toRotationMatrix();
	*/
		return Eigen::AngleAxisd(rpy(2), Vector3d::UnitZ()).toRotationMatrix() * Eigen::AngleAxisd(rpy(1), Vector3d::UnitY()).toRotationMatrix() * Eigen::AngleAxisd(rpy(0), Vector3d::UnitX()).toRotationMatrix();
	}
	/**
	 *@brief 根据RPY转换为变换矩阵
	 *@return 变换矩阵(4*4)
	 */
	//x,y,z order
	inline dmatrix rpy2tr(Position_MCS_rad posMCS)
	{
		dmatrix tr(4, 4);
		tr << rpy2r(posMCS.tail(3)), posMCS.head(3), dmatrix::Zero(1, 3), 1;
		return tr;
	}
	/**
	 *@brief rpy角度转换为弧度
	 *@return 弧度的rpy参数(block是从rpy的[3,0]开始的3*1用后面的代替)
	 */
	inline Position_MCS_rad posMCS_deg2rad(const Position_MCS_deg& rpy)
	{
		Position_MCS_rad ret(rpy);
		ret.block(3, 0, 3, 1) = deg2rad(rpy.block(3,0,3,1));
		return ret;
	}
	/**
	 *@brief rpy弧度转换为角度
	 *@return 角度的rpy参数
	 */
	inline Position_MCS_deg posMCS_rad2deg(const Position_MCS_rad& rpy)
	{
		Position_MCS_deg ret(rpy);
		ret.block(3, 0, 3, 1) = rad2deg(rpy.block(3,0,3,1));
		return ret;
	}
}

#endif