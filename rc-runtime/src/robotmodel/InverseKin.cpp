#include "InverseKin.h"
#include <iostream>

namespace RobotSpace{
	/**
	 *@brief 选择离当前位置最近的解，并确定方向
	 *@param 当前角度(radian)
	 *@param 解一
	 *@param 解二
	 *@return 
	 */
	double InverseKinInterface::calcRealAngle(double curAng, double candidateAng1,
			double candidateAng2) const{
		double curAngCopy(curAng);
		double* allAng[3] = { &candidateAng1, &candidateAng2, &curAngCopy };
		for (int i = 0; i < 3; ++i)
		{
			//将角度变换到-M_PI~M_PI范围
			while (*allAng[i]> M_PI)
			{
				*allAng[i] -= 2*M_PI;
			}
			while (*allAng[i] < -M_PI)
			{
				*allAng[i] += 2*M_PI;
			}
		}
		double gap[2] = { 0, 0 };
		bool dir[2] = { 1, 1 };//1 = true
		for (int i = 0; i < 2; ++i)
		{
			if (*allAng[i] >= curAngCopy)/*=*/
			{
				gap[i] = *allAng[i]-curAngCopy;
				dir[i] = true;      //正转
			}
			else
			{
				gap[i] = curAngCopy-*allAng[i];
				dir[i] = false;    //反转
			}
			if (gap[i]> M_PI)
			{
				gap[i] = 2*M_PI-gap[i];
				dir[i] = !dir[i];
			}
		}

		if (gap[0] <= gap[1])/*=*/
		{
			//		DEBUG("curAng = %f\r\n",rad2deg(curAng));
			//		DEBUG("gap[0] : gap[1] = %f - %f\r\n",rad2deg(gap[0]), rad2deg(gap[1]));
			//		DEBUG("curAng+gap[0] : curAng-gap[0] = %f - %f\r\n",rad2deg(curAng+gap[0]),rad2deg(curAng-gap[0]));
			return dir[0] ? curAng+gap[0] : curAng-gap[0];
		}
		else
		{
			//		DEBUG("curAng = %f\r\n",rad2deg(curAng));
			//		DEBUG("gap[0] : gap[1] = %f - %f\r\n",rad2deg(gap[0]), rad2deg(gap[1]));
			//		DEBUG("curAng+gap[1] : curAng-gap[1] = %f - %f\r\n",rad2deg(curAng+gap[1]), rad2deg(curAng-gap[0]));
			return dir[1] ? curAng+gap[1] : curAng-gap[1];
		}
	}

	int InverseNormal::calcInverseKin(const std::vector<std::shared_ptr<Axis>>& _axes, const Matrix4d& _baseMatrix, 
		const Matrix4d& _toolMatrix, const dmatrix& transMatrix, const Position_ACS_rad& posLast,Position_ACS_rad& posACS)
	{
		if ( (transMatrix.rows()!=4) || (transMatrix.cols() !=4)||(posLast.rows()
			!=6)||(posACS.rows() !=6) ||(_axes.size()!=6))
		{	
			std::cerr << "InverKin argument ERROR" << std::endl;
			return -1;
		}

		dmatrix T(transMatrix);
		T = _baseMatrix.inverse() * T;
		T *= _toolMatrix.inverse();

		Position_ACS_rad pLast(posLast);//读到的角度，经下面处理后，成为theta值

		double nx(T(0,0)), ny(T(1,0)), nz(T(2,0));
		double ox(T(0,1)), oy(T(1,1)), oz(T(2,1));
		double ax(T(0,2)), ay(T(1,2)), az(T(2,2));
		double px(T(0,3)), py(T(1,3)), pz(T(2,3));

		//vars defined temporarily
		double d1(_axes[0]->_paramDH.d);
		double d4(_axes[3]->_paramDH.d);
		double d6(_axes[5]->_paramDH.d);
		double a1(_axes[0]->_paramDH.a);
		double a2(_axes[1]->_paramDH.a);
		double a3(_axes[2]->_paramDH.a);

		//solve for theta1
		double theta1_1;
		if((fabs((d6*ay + py)) < 10e-13 ) && (fabs((d6*ax + px)) < 10e-13))
			theta1_1 = pLast(0);
		else
			theta1_1 = atan2((d6*ay + py),(d6*ax + px));
		double theta1_2 = theta1_1;
		double theta1;

		if (theta1_1 <= 0.0L)
			theta1_2 = theta1_1 + M_PI;
		else
			theta1_2 = theta1_1 - M_PI;

		theta1 = calcRealAngle(pLast(0), theta1_1, theta1_2);
		// the limit of theta1 according to the reference
		if((theta1 < -M_PI) || (theta1 > M_PI))
		{
			theta1 = pLast(0);
			std::cerr<< "theta1 exceeds pos limit."<< std::endl;
			return -1;
		}
		posACS(0) = theta1;

		//solve for theta3
		double k1 = d6*(cos(theta1)*ax + sin(theta1)*ay) +  
						cos(theta1)*px + sin(theta1)*py - a1;
		double k2 = d6*az + pz - d1;
		double k3 = pow(k1, 2) + pow(k2, 2) - pow(a2, 2) - pow(a3, 2) - pow(d4, 2);
		double k4 = k3/(2*a2);
		double temp_var = pow(a3, 2) + pow(d4, 2) - pow(k4, 2);
		if(temp_var < 0.0L)
		{
			std::cerr << "Theta3 can not be solved, so can not reach the point!" << std::endl;
			return -1;
		}
		double delta = sqrt(pow(a3, 2) + pow(d4, 2) - pow(k4, 2));
		double theta3_1 = atan2(d4, a3) + atan2(delta, k4);
		double theta3_2 = atan2(d4, a3) - atan2(delta, k4);
		double theta3;

		theta3 = calcRealAngle(pLast(2), theta3_1, theta3_2);
		// the limit of theta3 according to the reference
		if((theta3 < -170.0L/180.0L*M_PI) || (theta3 > 80.0L/180.0L*M_PI))
		{
			theta3 = pLast(2);
			std::cerr << "theta3 exceeds pos limit.\n" << std::endl;
			return -1;
		}
		posACS(2) = theta3;

		//solve for theta2
		k1 = cos(theta1)*px + sin(theta1)*py - a1 + d6*(cos(theta1)*ax + sin(theta1)*ay);
		k2 = d1 - pz - d6*az;
		double a = d4*cos(theta3) - a3*sin(theta3);
		double b = d4*sin(theta3) + a2 +a3*cos(theta3);
		//!!!已经加入了theta2的offset -pi/2    theta(运算) = theta(电机) - pi/2
	    double theta2_1;
	    if((fabs(a*k1 + b*k2) < 10e-13)  && (fabs(b*k1 - a*k2) < 10e-13))
	    	theta2_1 = pLast(1);
	    else
	    	theta2_1 = atan2((a*k1 + b*k2),(b*k1 - a*k2)) + M_PI/2.0;
	    double theta2;

	    theta2 = calcRealAngle(pLast(1), theta2_1, theta2_1);
	    // the limit of theta2 according to the reference
		if((theta2 < -60.0L/180.0L*M_PI) || (theta2 > 140.0L/180.0L*M_PI))
		{
			theta2 = pLast(1);
			std::cerr<< "theta2 exceeds pos limit.\n" << std::endl;
			return -1;
		}
		posACS(1) = theta2;

		k1 = -sin(theta1)*ax + cos(theta1)*ay;
		k2 = cos(theta1)*cos(theta2 - M_PI/2.0 + theta3)*ax + sin(theta1)*
				cos(theta2 - M_PI/2.0 + theta3)*ay - sin(theta2 - M_PI/2.0 + theta3)*az;

		double theta4;
		double theta4_2;
		//此处的判断阈值不能过小，过小的话，当0/0时，它无法识别出来
		if((fabs(k1) < 10e-13) && (fabs(k2) < 10e-13))
		{
			theta4 = pLast(3);
			//cout << "A" << endl;
		}
		else
		{
			double theta4_1 = atan2(-k1,-k2);
			if(theta4_1 > 0.0L)
				theta4_2 = theta4_1 - M_PI;
			else
				theta4_2 = theta4_1 + M_PI;
			theta4 = calcRealAngle(pLast(3), theta4_1, theta4_2);
		}

		// the limit of theta4 according to the reference
		if((theta4 < -2.0L*M_PI) || (theta4 > 2.0L*M_PI))
		{
			theta4 = pLast(3);
			std::cerr << "theta4 exceeds pos limit." << std::endl;
			return -1;
		}
		posACS(3) = theta4;


		//solve for theta5
		double k1_1 = -sin(theta1)*sin(theta4) + cos(theta1)*cos(theta4)*cos(theta2 - M_PI/2.0 + theta3);
		double k1_2 = cos(theta1)*sin(theta4) + sin(theta1)*cos(theta4)*cos(theta2 - M_PI/2.0 + theta3);
		double k1_3 = -cos(theta4)*sin(theta2 - M_PI/2.0 + theta3);
		k1 = k1_1*ax + k1_2*ay + k1_3*az;
		k2 = -cos(theta1)*sin(theta2 - M_PI/2.0 + theta3)*ax - sin(theta1)*sin(theta2 - M_PI/2.0 + theta3)*
				ay - cos(theta2 - M_PI/2.0 + theta3)*az;
		double theta5_1;
		if((fabs(k1) < 10e-13) && (fabs(k2) < 10e-13))
			theta5_1 = pLast(4);
		else
			theta5_1 = atan2(-k1, k2);
		double theta5;
		
		theta5 = calcRealAngle(pLast(4), theta5_1, theta5_1);	
		// the limit of theta5 according to the reference
		if((theta5 < -120.0L/180.0L*M_PI) || (theta5 > 135.0L/180.0L*M_PI))
		{
			theta5 = pLast(4);
			std::cerr << "theta5 exceeds pos limit." << std::endl;
			return -1;
		}
		posACS(4) = theta5; 
		
		//solve for theta6
		k1_1 = -cos(theta1)*sin(theta4)*cos(theta2 - M_PI/2.0 + theta3) - cos(theta4)*sin(theta1);
		k1_2 = cos(theta1)*cos(theta4) - sin(theta1)*sin(theta4)*cos(theta2 - M_PI/2.0 + theta3);
		k1_3 = sin(theta4)*sin(theta2 - M_PI/2.0 + theta3);
		k1 = k1_1*nx + k1_2*ny + k1_3*nz;
		k2 = k1_1*ox + k1_2*oy + k1_3*oz;
		double theta6_1;
		if((fabs(k1) < 10e-13) && (fabs(k2) < 10e-13))
			theta6_1 = pLast(5);
		else
			theta6_1 = atan2(k1, -k2);
		double theta6;
		
		theta6 = calcRealAngle(pLast(5), theta6_1, theta6_1);
		// the limit of theta6 according to the reference
		if((theta6 < -2.0L*M_PI) || (theta6 > 2.0L*M_PI))
		{
			theta6 = pLast(5);
			std::cerr << "theta6 exceeds pos limit." << std::endl;
			return -1;
		}
		posACS(5) = theta6;
		for (std::vector<std::shared_ptr<Axis>>::size_type sz=0; sz!=_axes.size(); ++sz)
		{
			if ( (posACS(sz)>deg2rad(_axes[sz]->_paramLim.max_pos)) || (posACS(sz) <deg2rad(_axes[sz]->_paramLim.min_pos)))
			{
				std::cerr << "theta "<<sz+1<<" exceeds pos limit\n";
				std::cerr << "posACS = [ \n" << rad2deg(posACS) <<" \n]\n";

				posACS = pLast;
				return -1;
			}
		}
		return 0;	
	}
}