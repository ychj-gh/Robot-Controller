#ifndef __AXIS_H__
#define __AXIS_H__
#include "../../../include/robotctl.h"
#include "RobotType.h"
#include "RobotUtility.h"
#include <string>

namespace RobotSpace{
	/**
	 * 　类Axis 注意DH_param和Lim_param中参数均以角度为单位
	 */
	class Axis{
	public:
		Axis(){}
		Axis(const Axis_param& axisP): _axisName(axisP.name),_paramDH(axisP.DH_p),
				_paramLim(axisP.Lim_p),_direction(axisP.dir),_offset(axisP.offset),_actualDeg(0.0){}
		Axis(const std::string& nm, const DH_param& DHp, const Lim_param& Limp, int dir, double off):
				_axisName(nm), _paramDH(DHp), _paramLim(Limp), _direction(dir), _offset(off),_actualDeg(0.0){}
		~Axis(){}
	public:
		Matrix4d compute() const {
			Matrix4d transform, X, Z;
			// Calculate Z with Z = TranslationZ(d).RotationZ(theta)
			// 绕Z轴旋转，平移
			Z << Eigen::AngleAxisd(deg2rad(_paramDH.theta), Vector3d::UnitZ()).toRotationMatrix(), 
				(dmatrix(3,1)<<0.0,0.0,_paramDH.d).finished(), dmatrix::Zero(1, 3), 1;
			// Calculate X with X = TranslationX(radius).RotationZ(alpha)
			// 绕X轴旋转，平移
			X << Eigen::AngleAxisd(deg2rad(_paramDH.alpha), Vector3d::UnitX()).toRotationMatrix(), 
				(dmatrix(3,1)<<_paramDH.a,0.0,0.0).finished(), dmatrix::Zero(1, 3), 1;
			// Calculate the transform with T=Z.X
			transform = Z*X;
			return transform;
		}

		double motor2RobotPos() const {
			return _direction * (_actualDeg - _offset);
		}

		/* 由于Estun机器人伺服系统偏差较大，可能需要将上一次的控制量作为这一次的初始位置　*/
		double motor2RobotPos(double motopos) const {
			return _direction * (motopos - _offset);
		}

		double robot2MotorPos(double rbtpos) const {
			return _direction * rbtpos + _offset;
		}

	public:
		std::string _axisName;
		DH_param  _paramDH;
		Lim_param _paramLim;
		int _direction;
		double _offset;
		double _actualDeg;		// 轴实际角度
	};
}

#endif