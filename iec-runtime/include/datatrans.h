#ifndef __DATATRANS_H__
#define __DATATRANS_H__
#include "../../include/robotctl.h"
#include "../../include/servo.h"

extern RT_COND   rc_cond_desc;				/* RC/PLC同步对象－－条件变量描述符 */
extern RT_MUTEX  rc_mutex_desc;				/* RC/PLC同步对象－－互斥量描述符 */
extern RT_MUTEX  sv_mutex_desc;				/* PLC/Servo同步对象－－互斥量描述符 */
extern RT_QUEUE	 mq_rc_interp_desc;			/* 消息队列描述符 PLC --> RC插补器 */
extern RT_QUEUE  mq_plc_desc;				/* 消息队列描述符 RC插补器 --> PLC */

extern SingleAxisInfo 	robot_actual_info_buffer[MAX_AXIS_COUNT];	/* 伺服轴实际位置中间变量 */
extern SingleInterpData  robot_interpdata_buffer[MAX_AXIS_COUNT];	/* 伺服控制输出中间变量 */

void rc_shm_servo_write(RCMem* rc_shm, SingleAxisInfo* axis_actual_info);
void rc_shm_servo_read(RCMem* rc_shm, SingleInterpData* axis_command_info);
void sv_shm_plc2servo(SVMem* sv_shm, SingleInterpData* axis_command_info);
void sv_shm_servo2plc(SVMem* sv_shm, SingleAxisInfo* axis_actual_info);

inline int send_cmd_to_interp(int command) {
    void *cmd ;
    cmd = rt_queue_alloc(&mq_rc_interp_desc, 1);
    (*(char*)cmd) = command;
    rt_queue_send(&mq_rc_interp_desc, cmd, 1, Q_NORMAL);
}

#endif 