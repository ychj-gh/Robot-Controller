#ifndef __ROBOT_TYPE_H__
#define __ROBOT_TYPE_H__

#include <Eigen/Eigen>
#include <memory>

namespace RobotSpace{
	// Eigen type
	typedef Eigen::Vector3d Vector3d;  /**< @brief 含有3个double型元素的列向量*/
	typedef Eigen::Vector4d Vector4d;  /**< @brief 含有4个double型元素的列向量*/
	typedef Eigen::MatrixXd dmatrix;  /**< @brief 含有n*mdouble型元素的矩阵*/
	typedef Eigen::Matrix3d Matrix3d;  /**< @brief 含有3*3double型元素的矩阵*/
	typedef Eigen::Matrix4d Matrix4d;  /**< @brief 含有4*4double型元素的矩阵*/
	typedef Eigen::VectorXd dvector;  /**< @brief 含有X个double型元素的列向量*/
	typedef dmatrix::Index dmIndex;
	typedef dvector::Index dvIndex;
	typedef Eigen::Quaterniond dQuaternion;  /**< @brief double型四元组*/
	#define	Identity3	Eigen::MatrixXd::Identity(3,3)		/**< @brief 3x3单位阵*/
	#define	Identity4	Eigen::MatrixXd::Identity(4,4)		/**< @brief 4x4单位阵*/


	// Robot type
	// Position
	typedef dvector Position_ACS_deg;	/**< @brief 关节坐标系位置　unit: degree*/
	typedef dvector Position_ACS_rad;	/**< @brief 关节坐标系位置 unit: radian*/
	typedef dvector Position_MCS_deg;	/**< @brief 直角空间　unit: mm, degree*/
	typedef dvector Position_MCS_rad;	/**< @brief 直角空间　unit: mm, radian*/
	// Velocity
	typedef dvector Velocity_ACS_deg;	/**< @brief 关节空间速度　unit: degree/s*/
	typedef dvector Velocity_ACS_rad;	/**< @brief 关节空间速度　unit: radian/s*/
	typedef dvector Velocity_MCS_deg;	/**< @brief 直角空间速度　unit: mm/s, degree/s*/
	typedef dvector Velocity_MCS_rad;	/**< @brief 直角空间速度　unit: mm/s, radian/s*/
	// Accelerate
	typedef dvector Accelerate_ACS_deg;	/**< @brief 关节空间加速度　unit: degree/s^2*/
	typedef dvector Accelerate_ACS_rad;	/**< @brief 关节空间加速度　unit: radian/s^2*/
	typedef dvector Accelerate_MCS_deg;	/**< @brief 直角空间加速度　unit: mm/s^2 degree/s^2*/
	typedef dvector Accelerate_MCS_rad;	/**< @brief 直角空间加速度　unit: mm/s^2 radian/s^2*/

	// nurbs插补所需类型
	typedef dvector Position;
	// U矢量　w矢量
	typedef dvector vectorU;
	typedef dvector vectorW;

	typedef Eigen::Vector3d XYZ;
	typedef Eigen::Vector3d RPY;

	class Axis;
	// typedef std::shared_ptr<Axis> AXIS_REF;
	// typedef std::vector<AXIS_REF>::size_type AXIS_REFS_INDEX;
	// 参考坐标系
	enum COORD_SYS{
		ACS = 0,						/**< @brief 关节坐标系　*/
		MCS = 1 						/**< @brief 直角空间坐标系*/
	};
}

#endif