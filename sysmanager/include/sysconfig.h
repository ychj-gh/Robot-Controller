#ifndef __SYS_CONFIG__
#define __SYS_CONFIG__
#include "tinyxml.h"
#include "tinystr.h"
#include "io.h"
#include "servo.h"
#include "robotctl.h"

static int verify_obj(TiXmlNode* node);
static int load_io_config(TiXmlNode* node, IOConfig *io_config);
static int load_servo_config(TiXmlNode* node, ServoConfig *sv_conf);
static int load_robot_config(TiXmlNode* node, RobotConfig* rc_conf);
int SystemConfig();

#endif