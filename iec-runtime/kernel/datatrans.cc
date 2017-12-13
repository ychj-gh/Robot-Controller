#include "datatrans.h"

SingleAxisInfo 	robot_actual_info_buffer[MAX_AXIS_COUNT];   /* 伺服轴实际位置中间变量 */
SingleInterpData  robot_interpdata_buffer[MAX_AXIS_COUNT];	/* 伺服控制输出中间变量 */

/**
 * 函数名：rc_shm_servo_write
 * 功能：PLC向RC共享内存数据区写入伺服电机实际位置、速度、加速度信息；
 *      首先获得同步互斥量，然后写入数据，最后释放同步互斥量。
 * 参数：rc_shm：内存共享区指针
 *      axis_actual_info：伺服电机实际位置、速度、加速度信息变量
 * 返回值：无
 */
void rc_shm_servo_write(RCMem* rc_shm, SingleAxisInfo* axis_actual_info){
	rt_mutex_acquire(&rc_mutex_desc, TM_INFINITE);
	for(int i = 0; i < rc_shm->data.axis_count; ++i){
		rc_shm->data.axis_info[i].actual_pos = axis_actual_info[i].actual_pos;
		// rc_shm->data.axis_info[i].actual_vel = axis_actual_info[i].actual_vel;
		// rc_shm->data.axis_info[i].actual_acc = axis_actual_info[i].actual_acc;
	}
	rt_mutex_release(&rc_mutex_desc);
} 

/**
 * 函数名：rc_shm_servo_read
 * 功能：PLC向共享内存数据区读取控制伺服电机运动的位置、速度、加速度信息；
 *      使用消息队列，首先向RC插补器消息队列发送1，然后等待插补器线程计算完成向PLC进程发送消息
 * 参数：rc_shm：内存共享区指针
 *      axis_command_info：控制伺服电机输出位置、速度、加速度信息变量
 * 返回值：无
 */
void rc_shm_servo_read(RCMem* rc_shm, SingleInterpData* axis_command_info){
	void* request;
	request = rt_queue_alloc(&mq_rc_interp_desc,1);
	(*(char* )request) = 1;
	rt_queue_send(&mq_rc_interp_desc, request, 1, Q_NORMAL);

	void* response;
	rt_queue_receive(&mq_plc_desc, &response, TM_INFINITE);
	for(int i = 0; i < rc_shm->data.axis_count; ++i){
		axis_command_info[i].command_pos = rc_shm->data.interp_value[i].command_pos;
		axis_command_info[i].command_vel = rc_shm->data.interp_value[i].command_vel;
		axis_command_info[i].command_acc = rc_shm->data.interp_value[i].command_acc;
	}
	rt_queue_free(&mq_plc_desc,response);
}

/**
 * 函数名：sv_shm_plc2servo
 * 功能：PLC向伺服映像区发送运动的位置、速度、加速度信息；
 *      首先获得同步互斥量，然后写入数据，最后释放同步互斥量。
 * 参数：sv_shm：伺服映像区指针
 *      axis_command_info：控制伺服电机输出位置、速度、加速度信息变量
 * 返回值：无
 */
void sv_shm_plc2servo(SVMem* sv_shm, SingleInterpData* axis_command_info){
	rt_mutex_acquire(&sv_mutex_desc, TM_INFINITE);
	for(int i = 0; i < sv_shm->axis_count; ++i){
		sv_shm->axis_data[i].command_pos = axis_command_info[i].command_pos;
		sv_shm->axis_data[i].command_vel = axis_command_info[i].command_vel;
		sv_shm->axis_data[i].command_acc = axis_command_info[i].command_acc;
	}
	rt_mutex_release(&sv_mutex_desc);
}

/**
 * 函数名：sv_shm_servo2plc
 * 功能：PLC从伺服映像区读取伺服电机实际位置、速度、加速度信息；
 *      首先获得同步互斥量，然后读取数据，最后释放同步互斥量。
 * 参数：sv_shm：伺服映像区指针
 *      axis_actual_info：伺服电机实际位置、速度、加速度信息变量
 * 返回值：无
 */
void sv_shm_servo2plc(SVMem* sv_shm, SingleAxisInfo* axis_actual_info){
	rt_mutex_acquire(&sv_mutex_desc, TM_INFINITE);
	for(int i = 0; i < sv_shm->axis_count; ++i){
		axis_actual_info[i].actual_pos = sv_shm->axis_data[i].actual_pos;
		axis_actual_info[i].actual_vel = sv_shm->axis_data[i].actual_vel;
		axis_actual_info[i].actual_acc = sv_shm->axis_data[i].actual_acc;
	}
	rt_mutex_release(&sv_mutex_desc);
}