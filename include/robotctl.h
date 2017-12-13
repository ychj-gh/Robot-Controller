#ifndef __ROBOTCTL__
#define __ROBOTCTL__
#include <stdint.h>
#include <native/heap.h>
#include <native/mutex.h>
#include <native/cond.h>
#include <native/queue.h>
// #include "servo.h"
#include "logger.h"
#include "syslimit.h"
#include <stdio.h>

#define MAX_AXIS_COUNT      10
#define MAX_ROBOT_NAME_SIZE	16
#define RC_CONFIG_SIZE		(sizeof(RobotConfig))
#define RC_CONFIG_NAME		"rc_conf"

enum ROBOT_TYPE{
	GENERAL_RBT_TYPE,
	OTHERS
};

struct DH_param{
	double theta;
	double d;
	double a;
	double alpha;
	double offset;							/* 机器人初始theta角 */
};

struct Lim_param{
	double min_pos;							/* 反向最大位置(单位：度) */
	double max_pos;							/* 正向最大位置(单位：度) */
	double max_vel;							/* 最大速度 */
	double max_acc;							/* 最大减速度 */
	double max_dec;							/* 最大减速度 */
	double max_jerk;						/* 最大加加速度 */
};

typedef struct{
	char name[MAX_AXIS_NAME_SIZE];			/*　轴名称　*/
	int dir;								/* 轴正方向与所建机器人坐标系是否一致　*/
	DH_param DH_p;							/* 轴DH参数 */
	Lim_param Lim_p;						/* 轴极限参数 */
	double offset;							/* 机器人零点与轴零点偏移 */
}Axis_param;

typedef struct{
	char name[MAX_ROBOT_NAME_SIZE];			/* 机器人名称　*/
	uint8_t axis_count;						/* 机器人轴数 */
	ROBOT_TYPE robot_type;					/* 机器人型号 */
	Axis_param axis[MAX_AXIS_COUNT];		/* 机器人配置参数 */
	double toolMatrix[4][4]; 				/* 工具坐标系矩阵 */
	double baseMatrix[4][4];				/* 基坐标系在世界坐标系下的矩阵　*/
}RobotConfig;

/**--------------------------------------------------------------
  * 机器人配置共享区
  *-------------------------------------------------------------*/
inline void rc_conf_create(RT_HEAP *heap, RobotConfig **conf){
	if(rt_heap_create(heap,RC_CONFIG_NAME,RC_CONFIG_SIZE,H_SHARED) < 0)
		LOGGER_ERR(E_HEAP_CREATE, "(name=%s, size=%d)", RC_CONFIG_NAME, RC_CONFIG_SIZE);
	if(rt_heap_alloc(heap,RC_CONFIG_SIZE,TM_INFINITE,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d)", RC_CONFIG_NAME, RC_CONFIG_SIZE);
}

inline void rc_conf_bind(RT_HEAP *heap, RobotConfig **conf){
	if(rt_heap_bind(heap,RC_CONFIG_NAME,TM_INFINITE) < 0)
		LOGGER_ERR(E_HEAP_BIND, "(name=%s, size=%d)", RC_CONFIG_NAME, RC_CONFIG_SIZE);
	if(rt_heap_alloc(heap,0,TM_NONBLOCK,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d)", RC_CONFIG_NAME, RC_CONFIG_SIZE);
}

inline void rc_conf_unbind(RT_HEAP *heap){
	if(rt_heap_unbind(heap) < 0)
		LOGGER_ERR(E_HEAP_UNBIND,"(name=%s)",RC_CONFIG_NAME);
}

inline void rc_conf_delete(RT_HEAP *heap){
	if(rt_heap_delete(heap) < 0)
		LOGGER_ERR(E_HEAP_DELETE, "(name=%s, size=%d)", RC_CONFIG_NAME, RC_CONFIG_SIZE);
}

/*-----------------------------------------------------------------------------
 * PLC/RC共享内存数据结构及堆创建操作函数
 *---------------------------------------------------------------------------*/
#define RC_MEM_NAME	"rc_mem"
#define GENERAL_VAR_COUNT 	4096			// 4k个
#define SHM_RC_MODE_GET(rc_shm)		  ((rc_shm->StatusWord)& 0x01)
#define SHM_INTERP_START_GET(rc_shm)  ((rc_shm->StatusWord>>1)& 0x01)
#define SHM_INTERP_STATUS_GET(rc_shm) ((rc_shm->StatusWord>>2)& 0x01)
#define SHM_PLC_START_GET(rc_shm)	  ((rc_shm->StatusWord>>3)& 0x01)
#define SHM_RC_ALLOW_GET(rc_shm)	  ((rc_shm->StatusWord>>4)& 0x01)

#define SHM_RC_MODE_SET(rc_shm)		((rc_shm->StatusWord)|= 0x01)
#define SHM_INTERP_START_SET(rc_shm)	((rc_shm->StatusWord)|= 0x02)
#define SHM_INTERP_STATUS_SET(rc_shm)	((rc_shm->StatusWord)|= 0x04)
#define SHM_PLC_START_SET(rc_shm)	((rc_shm->StatusWord)|= 0x08)
#define SHM_RC_ALLOW_SET(rc_shm)	((rc_shm->StatusWord)|= 0x10)

#define SHM_RC_MODE_CLR(rc_shm)		((rc_shm->StatusWord)&= 0xfe)
#define SHM_INTERP_START_CLR(rc_shm)	((rc_shm->StatusWord)&= 0xfd)
#define SHM_INTERP_STATUS_CLR(rc_shm)	((rc_shm->StatusWord)&= 0xfb)
#define SHM_PLC_START_CLR(rc_shm)	((rc_shm->StatusWord)&= 0xf7)
#define SHM_RC_ALLOW_CLR(rc_shm)	((rc_shm->StatusWord)&= 0xef)

struct GenVar{								/* 通用变量数据区 */
	int8_t  var_byte[GENERAL_VAR_COUNT];	/* 字节型变量 */
	int32_t var_int[GENERAL_VAR_COUNT];		/* 4字节int型变量 */
	float	var_float[GENERAL_VAR_COUNT]; 	/* 4字节浮点型变量 */
};

struct SingleInterpData{					/* 单轴插补数据 */
	double command_pos;
	double command_vel;
	double command_acc;
};

struct SingleAxisInfo{						/* 单轴实际位置 */
	double actual_pos;
	double actual_vel;
	double actual_acc;
};

struct AxisDataExchange{							/* 伺服轴数据交互区 */
	uint8_t axis_count;
	int dir[MAX_AXIS_COUNT];						/* 轴正方向与所建机器人坐标系是否一致　*/
	double offset[MAX_AXIS_COUNT];					/* 机器人零点与轴零点偏移 */
	SingleInterpData interp_value[MAX_AXIS_COUNT]; 	/* 插补数据 */
	SingleAxisInfo 	 axis_info[MAX_AXIS_COUNT];	   	/* 轴数据实际值 */
};

struct RCMem{
	uint8_t StatusWord;						/* 状态标志字 */
	GenVar 	General_variable;				/* 通用变量数据区 */
											/* I/O 变量区 */
	AxisDataExchange data;					/* 伺服轴数据交互区 */
};

/**
 * 函数功能： 创建RC共享区堆
 * heap 创建堆描述符 rcmem 指向RC共享内存区指针的指针
 */
inline void rc_mem_create(RT_HEAP* heap, RCMem** rcmem){
	int size = sizeof(RCMem);
	int ret = 0;
	if((ret = rt_heap_create(heap, RC_MEM_NAME, size, H_SHARED)) < 0)
		LOGGER_ERR(E_HEAP_CREATE, "(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
	if((ret = rt_heap_alloc(heap,size,TM_INFINITE,(void **)rcmem)) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
}

/**
 * 函数功能： RC/PLC共享内存区初始化
 * rcmem 指向RC共享内存区的指针 config 指向RC配置区指针
 */
inline void rc_mem_init(RCMem* rcmem, RobotConfig* config){
	rcmem->StatusWord = 0;
	memset(rcmem->General_variable.var_byte,0,sizeof(GenVar));
	rcmem->data.axis_count = config->axis_count;
	for(int i = 0; i < MAX_AXIS_COUNT; ++i){
		rcmem->data.dir[i] = config->axis[i].dir;
		rcmem->data.offset[i] = config->axis[i].offset;
		rcmem->data.interp_value[i].command_pos = 0.0;
		rcmem->data.interp_value[i].command_vel = 0.0;
		rcmem->data.interp_value[i].command_acc = 0.0;
		rcmem->data.axis_info[i].actual_pos = 0.0;
		rcmem->data.axis_info[i].actual_vel = 0.0;
		rcmem->data.axis_info[i].actual_acc = 0.0;
	}
}

/**
 * 函数功能： 将堆描述符绑定到有RC_MEM_NAEM的堆
 * heap 创建堆描述符 rcmem 指向RC共享内存区指针的指针
 */
inline void rc_mem_bind(RT_HEAP* heap, RCMem** rcmem){
	int size = sizeof(RCMem);
	int ret = 0;
	if((ret = rt_heap_bind(heap, RC_MEM_NAME, TM_INFINITE)) < 0)
		LOGGER_ERR(E_HEAP_BIND,"(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
	if((ret = rt_heap_alloc(heap, 0,TM_NONBLOCK, (void **)rcmem)) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
}

/**
 * 函数功能： 解除绑定描述符
 * heap 创建堆描述符 rcmem 指向RC共享内存区指针的指针
 */
inline void rc_mem_unbind(RT_HEAP* heap, RCMem** rcmem){
	int size = sizeof(RCMem);
	int ret = 0;
	if((ret = rt_heap_unbind(heap)) < 0)
		LOGGER_ERR(E_HEAP_UNBIND,"(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
}


inline void rc_mem_delete(RT_HEAP* heap){
	int size = sizeof(RCMem);
	int ret = 0;
	if((ret = rt_heap_delete(heap)) < 0)
		LOGGER_ERR(E_HEAP_DELETE,"(name=%s, size=%d, ret=%d)", RC_MEM_NAME,size,ret);
}

/*-----------------------------------------------------------------------------
 * PLC/RC共享内存同步操作函数
 *---------------------------------------------------------------------------*/
#define RC_MUTEX_NAME	"rc_mutex"
#define RC_COND_NAME	"rc_cond"
#define MQ_RC_INTERP_NAME   "mq_rc_interp"  //  ---> interp 消息队列名
#define MQ_PLC_NAME    		"mq_plc"  // interp ---> plc 消息队列名

/**
 * 函数功能： 创建RC/PLC同步对象 互斥锁 条件变量
 * mutex_desc 互斥锁描述符 cond_desc 条件变量描述符
 */
inline void rc_syncobj_create(RT_MUTEX* mutex_desc, RT_COND* cond_desc){
	int ret = 0;
	if((ret = rt_mutex_create(mutex_desc, RC_MUTEX_NAME)) < 0)
		LOGGER_ERR(E_RCMUTEX_CREATE, "(name=%s, ret=%d)", RC_MUTEX_NAME,ret);
	if((ret = rt_cond_create(cond_desc,RC_COND_NAME)) < 0)
		LOGGER_ERR(E_RCCOND_CREATE, "(name=%s, ret=%d)",RC_COND_NAME,ret);
}

/**
 * 函数功能： 销毁RC/PLC同步对象 互斥锁 条件变量
 * mutex_desc 互斥锁描述符 cond_desc 条件变量描述符
 */
inline void rc_syncobj_delete(RT_MUTEX* mutex_desc, RT_COND* cond_desc){
	if(rt_mutex_delete(mutex_desc) < 0)
		LOGGER_ERR(E_RCMUTEX_DEL,"(name=%s)",RC_MUTEX_NAME);
	if(rt_cond_delete(cond_desc) < 0)
		LOGGER_ERR(E_RCCOND_DEL, "(name=%s)",RC_COND_NAME);
}

/**
 * 函数功能： bind RC/PLC同步对象 互斥锁 条件变量
 * mutex_desc 互斥锁描述符 cond_desc 条件变量描述符
 */
inline void rc_syncobj_bind(RT_MUTEX* mutex_desc,RT_COND* cond_desc){
	int ret = 0;
	if((ret = rt_mutex_bind(mutex_desc,RC_MUTEX_NAME,TM_INFINITE)) < 0)
		LOGGER_ERR(E_RCMUTEX_BIND,"(name=%s, ret=%d)",RC_MUTEX_NAME,ret);
	if((ret = rt_cond_bind(cond_desc,RC_COND_NAME,TM_INFINITE)) < 0)
		LOGGER_ERR(E_RCCOND_BIND,"(name=%s, ret=%d)",RC_COND_NAME,ret);
}

#endif