#ifndef __SERVO_H__
#define __SERVO_H__
#include <stdint.h>
#include <native/heap.h>
#include <native/mutex.h>
#include "logger.h"
#include "robotctl.h"
#include "syslimit.h"

// #define MAX_AXIS_NAME_SIZE	10
//#define MAX_AXIS_COUNT		10

#define SV_CONFIG_SIZE 		(sizeof(ServoConfig))
#define SV_CONFIG_NAME  	"sv_conf"

typedef struct{
	char name[MAX_AXIS_NAME_SIZE];			/* 轴名称 */
	uint8_t pid;							/* 设备总线地址编号 */								
	uint8_t id;								/* 轴编号 */
	uint8_t type;							/* 类型：旋转轴 | 滑动轴 */
	double min_pos;							/* 反向最大位置(单位：度) */
	double max_pos;							/* 正向最大位置(单位：度) */
	uint8_t ratio;							/* 减速比 */
	uint32_t encode;						/* 编码器精度 */
}AxisConfig;

typedef struct{
	uint8_t opmode;							/* 运行模式 */
	uint8_t axis_count;						/* 轴个数 */	
	uint32_t update_interval;				/* 伺服数据刷新周期 */
	AxisConfig axis_config[MAX_AXIS_COUNT]; /* 轴配置信息数组 */
}ServoConfig;

/**---------------------------------------------------------------
 *	伺服配置域共享内存调用
 * ---------------------------------------------------------------*/
inline void sv_conf_create(RT_HEAP *heap, ServoConfig **conf){
	if(rt_heap_create(heap,SV_CONFIG_NAME,SV_CONFIG_SIZE,H_SHARED) < 0)
		LOGGER_ERR(E_HEAP_CREATE, "(name=%s, size=%d)", SV_CONFIG_NAME, SV_CONFIG_SIZE);
	if(rt_heap_alloc(heap,SV_CONFIG_SIZE,TM_INFINITE,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d)", SV_CONFIG_NAME, SV_CONFIG_SIZE);
}

inline void sv_conf_bind(RT_HEAP *heap, ServoConfig **conf){
	if(rt_heap_bind(heap, SV_CONFIG_NAME, TM_INFINITE) < 0)
		LOGGER_ERR(E_HEAP_BIND, "(name=%s, size=%d)", SV_CONFIG_NAME, SV_CONFIG_SIZE);
	if(rt_heap_alloc(heap,0,TM_NONBLOCK,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d)", SV_CONFIG_NAME, SV_CONFIG_SIZE);
}

inline void sv_conf_unbind(RT_HEAP *heap){
	if(rt_heap_unbind(heap) < 0)
		LOGGER_ERR(E_HEAP_UNBIND,"(name=%s)",SV_CONFIG_NAME);
}

inline void sv_conf_delete(RT_HEAP *heap){
	if(rt_heap_delete(heap) < 0)
		LOGGER_ERR(E_HEAP_DELETE, "(name=%s, size=%d)", SV_CONFIG_NAME, SV_CONFIG_SIZE);
}

/*-----------------------------------------------------------------------------
 * 伺服映像区共享内存数据结构及操作函数
 *---------------------------------------------------------------------------*/
#define SV_MEM_NAME  "sv_mem"
#define SV_MEM_SIZE (sizeof(SVMem))
// data_status
#define DATA_OUT_OF_TIME  	0
#define DATA_NEW			1
// AXIS_CTRL_AREA ControlWord
#define SERVO_STOP			0
#define SERVO_RUN			1
// AXIS_CTRL_AREA PowerOnFlag
#define POWERED_OFF			0
#define POWERED_ON			1
typedef struct{
	uint32_t ControlWord;		/* 控制字 */
	uint32_t OperateMode;		/* 运行模式 */
	uint32_t PowerOnFlag;		/* 伺服上电完成标志 */
}AXIS_CTRL_AREA;				/* 对所有伺服轴控制 */

typedef struct{
	uint32_t ID;				/* 从站设备ID */
	uint32_t ErrorCode;			/* 出错码 */
	uint32_t StatusWord;		/* 状态字 */
}AXIS_STATUS_AREA;				/* 伺服轴状态区 */

typedef struct {
    double actual_pos;			/* 实际位置 */
    double actual_vel;			/* 实际速度 */
    double actual_acc;			/* 实际加速度 */
    double command_pos;			/* 目标位置 */
    double command_vel;			/* 目标速度 */
    double command_acc;			/* 目标加速度 */
} AXIS_DATA; 					/* 轴运动数据区 */

typedef struct{
	uint8_t axis_count;			/* 伺服轴个数 */
	uint8_t data_status;		/* 插补数据是否为过时数据 DATA_OUT_OF_TIME：过时 DATA_NEW：未过时 */
	AXIS_CTRL_AREA ctrl_area;	/* 伺服主站控制域 */
	AXIS_STATUS_AREA status_area[MAX_AXIS_COUNT];	/* 伺服从站状态域 */
	AXIS_DATA	axis_data[MAX_AXIS_COUNT];			/* 轴运动数据域 */
}SVMem;							/* 伺服映像区数据结构 */

/**
 * 函数功能： 创建伺服映像区堆
 * heap 创建堆描述符 svmem 指向伺服映像区指针地址
 */
inline void sv_mem_create(RT_HEAP* heap,SVMem** svmem){
	int size = sizeof(SVMem);
	int ret = 0;
	if((ret = rt_heap_create(heap, SV_MEM_NAME, size, H_SHARED)) < 0)
		LOGGER_ERR(E_HEAP_CREATE, "(name=%s, size=%d, ret=%d)", SV_MEM_NAME,size,ret);
	if((ret = rt_heap_alloc(heap, size, TM_INFINITE, (void **)svmem)) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d, ret=%d)",SV_MEM_NAME,size,ret);
}

/**
 *	函数功能：伺服映像区初始化
 *	svmem 伺服映像区指针 初始状态伺服映像区内数据无效
 */
inline void sv_mem_init(SVMem* svmem, ServoConfig *config){
	memset(svmem,0,sizeof(SVMem));
	svmem->axis_count = config->axis_count;
	svmem->data_status = DATA_OUT_OF_TIME;
}

/**
 *	函数功能：将堆描述符绑定到有SV_MEM_NAME的内存
 *	heap 创建堆描述符 svmem 指向伺服映像区指针地址
 */
inline void sv_mem_bind(RT_HEAP* heap, SVMem** svmem){
	int size = sizeof(SVMem);
	int ret = 0;
	if((ret = rt_heap_bind(heap, SV_MEM_NAME, TM_INFINITE)) < 0)
		LOGGER_ERR(E_HEAP_BIND, "(name=%s, size=%d, ret=%d)",SV_MEM_NAME,size,ret);
	if((ret = rt_heap_alloc(heap, size, TM_INFINITE, (void **)svmem)) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name=%s, size=%d, ret=%d)",SV_MEM_NAME,size,ret);
}

/**
 *	函数功能：解除绑定描述符
 *	heap 创建堆描述符 svmem 指向伺服映像区指针地址
 */
inline void sv_mem_unbind(RT_HEAP* heap, SVMem** svmem){
	int size = sizeof(SVMem);
	int ret = 0;
	if((ret = rt_heap_unbind(heap)) < 0)
		LOGGER_ERR(E_HEAP_UNBIND, "(name=%s, size=%d, ret=%d)", SV_MEM_NAME,size,ret);
}


inline void sv_mem_delete(RT_HEAP *heap){
	if(rt_heap_delete(heap) < 0)
		LOGGER_ERR(E_HEAP_DELETE, "(name=%s, size=%d)", SV_MEM_NAME, SV_MEM_SIZE);
}

/*-----------------------------------------------------------------------------
 * 伺服数据域共享内存同步对象操作函数
 *---------------------------------------------------------------------------*/
#define SV_MUTEX_NAME 	"sv_mutex"

/**
 *	函数功能：创建伺服同步对象
 *	mutex_desc 伺服互斥锁描述符
 */
inline void sv_syncobj_create(RT_MUTEX* mutex_desc){
	if(rt_mutex_create(mutex_desc, SV_MUTEX_NAME) < 0)
		LOGGER_ERR(E_SVMUTEX_CREATE, "name(%s)", SV_MUTEX_NAME);
}

/**
 *	函数功能：删除伺服同步对象
 *	mutex_desc 伺服互斥锁描述符
 */
inline void sv_syncobj_delete(RT_MUTEX* mutex_desc){
	if(rt_mutex_delete(mutex_desc) < 0)
		LOGGER_ERR(E_SVMUTEX_DEL, "name(%s)",SV_MUTEX_NAME);
}

/**
 *	函数功能：绑定伺服同步对象
 *	mutex_desc 伺服互斥锁描述符
 */
inline void sv_syncobj_bind(RT_MUTEX* mutex_desc){
	if(rt_mutex_bind(mutex_desc, SV_MUTEX_NAME, TM_INFINITE) < 0)
		LOGGER_ERR(E_SVMUTEX_BIND, "name(%s)", SV_MUTEX_NAME);
}

#endif