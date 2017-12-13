#ifndef __INVERSEKIN_H__
#define __INVERSEKIN_H__

#include "Axis.h"
#include "RobotType.h"
#include "RobotUtility.h"
#include <vector>

namespace RobotSpace{
	class InverseKinInterface{
	public:
		InverseKinInterface(){}
		virtual ~InverseKinInterface(){}
	public:
		virtual int calcInverseKin(const std::vector<std::shared_ptr<Axis>>&, const Matrix4d&, const Matrix4d&,
			const dmatrix&, const Position_ACS_rad&, Position_ACS_rad&) = 0 ;
	protected:
		double calcRealAngle(double curAng, double candidateAng1,double candidateAng2) const;
	};

	class InverseNormal:public InverseKinInterface{
	public:
		InverseNormal(){}
		int calcInverseKin(const std::vector<std::shared_ptr<Axis>>&, const Matrix4d&, const Matrix4d&,
			const dmatrix&, const Position_ACS_rad&, Position_ACS_rad&);
	};
}
#endif