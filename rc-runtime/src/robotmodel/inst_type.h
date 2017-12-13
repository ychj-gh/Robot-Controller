#ifndef __INST_TYPE_H__
#define __INST_TYPE_H__


#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "../../../include/robotctl.h"
#include "RobotType.h"

enum INST_TYPE{
	PTP,
	LIN,
	CIRC,
	JOINTJOG,
    CARTJOG,
    AXIS_ADJUST,
    CART_ADJUST
};

struct JogJointParam{
	int jointindex;   // index of axis
    int direction;    // POSITIVE or NEGTIVE
    int refsys;       // adapt mode: AXIS = 0 BASE = 1 or TOOL = 2
};



struct PosParam{
    RobotSpace::Position_ACS_deg apv;       // 关节角度值    deg
    RobotSpace::Position_MCS_rad cpv;       // 机器人末端位姿　mm rad
    JogJointParam jjp;
public:
	PosParam(){}
	~PosParam(){}
};


struct ROBOT_INST{
	INST_TYPE  ri_type;
	PosParam args[4];
public:
	ROBOT_INST(){}
	~ROBOT_INST(){}

	ROBOT_INST& operator=(ROBOT_INST& order){
        this->ri_type = order.ri_type;
        if(order.ri_type == PTP || order.ri_type == AXIS_ADJUST){
            this->args[0].apv = order.args[0].apv;
            this->args[1].apv = order.args[1].apv;
        } else if(order.ri_type == JOINTJOG || order.ri_type == CARTJOG) {
        	this->args[0].apv = order.args[0].apv;
        	this->args[0].jjp = order.args[0].jjp;
        } else if(order.ri_type == LIN) {
            this->args[0].apv = order.args[0].apv;
            this->args[1].cpv = order.args[1].cpv;
        } else if(order.ri_type == CIRC) {

        }
        else if(order.ri_type == CART_ADJUST)
        {
            this->args[0].apv = order.args[0].apv;
            this->args[0].jjp = order.args[0].jjp;
            this->args[1].cpv = order.args[1].cpv;
        }
        return *this;
    }
};

enum JogProc
{
	JOG_INCONSTACC = 0,
	JOG_CONSTVEL,
	JOG_STOP
};


 #define    BASE     1
 #define    TOOL     2

extern ROBOT_INST robot_inst_code;
extern bool flag;

#endif