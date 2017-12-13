#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <native/task.h>
#include "ivalue.h"
#include "istring.h"
#include "callstk.h"
#include "opcode.h"
#include "../../include/syslimit.h"
// #include "comanager.h"

/*-----------------------------------------------------------------------------
 * PLC Task Model
 *---------------------------------------------------------------------------*/
typedef struct{
    uint8_t task_index;             /* plc任务下标 */
    uint16_t current;               /* 信号源下标 */
    uint64_t last;                  /* 信号源上一次的值 */
}signalval_t;

typedef struct{
    uint8_t count;                  /* 信号个数 */
    std::vector<signalval_t> sig;   /* 信号信息 */
}signalset_t;
 
typedef struct{
    char name[MAX_TASK_NAME_SIZE];  /* 软PLC任务名 */
    uint8_t priority;               /* 任务优先级 */
    uint8_t type;                   /* 任务类型 SIGNAL|INTERVAL */
    uint16_t signal;                /* 信号源 TIMER|I/O */
    uint32_t interval;              /* 时间间隔 （ns）*/
    uint32_t sp_size;               /* 字符串池容量 */
    uint16_t cs_size;               /* 调用栈容量 */
    uint16_t pou_count;             /* 用户级POU个数 */
    uint16_t const_count;           /* 常量个数 */
    uint16_t global_count;          /* 全局变量个数 */
    uint16_t refval_count;          /* 引用变量个数 */
    uint32_t inst_count;            /* 指令个数 */
}TaskDesc;                          /* 软PLC任务描述符 */

typedef struct{
    char name[MAX_POU_NAME_SIZE];   /* 用户级POU名称 */
    uint8_t pou_type;               /* POU类型 函数、功能块、程序 */
    uint32_t pou_instance;          /* 功能块实例 */
    uint8_t input_count;            /* 输入参数个数 */
    uint8_t inout_count;            /* 输入输出参数个数 */
    uint8_t output_count;           /* 输出参数个数 */
    uint8_t local_count;            /* 局部变量个数 */
    uint32_t entry;                 /* 用户POU入口地址 */
}UPOUDesc;                          /* 用户级POU描述符 */

typedef struct{
    int8_t task_index;
    TaskDesc task_desc;             /* PLC任务描述符 */
    StrPool strpool;                /* 字符串池 */
    UPOUDesc *pou_desc;             /* 用户POU描述符 */
    IValue  *vconst;                /* 常量段指针 */
    IValue  *vglobal;               /* 全局变量段指针 */
    Ref_data vref;                  /* 复杂数据类型列表 */
    Instruction *code;              /* 代码段指针 */
    CStack stack;                   /* 调用栈 */
    uint32_t pc;                    /* 软PLC程序指针 */
}PLCTask;                           /* 软PLC任务模型 */

typedef struct{
    uint8_t task_count;             /* 任务个数 */
    uint16_t tasks_global_count;    /* 任务间全局变量的个数 */
    uint16_t timer_count;           /* 运行系统中定时器的个数 */
    signalset_t signal_set;         /* 事件任务信号源信息 */
    IValue  *plcglobal;             /* 任务间全局变量指针 */
    RT_TASK *rt_task;
    RT_TASK_INFO *rt_info;
    PLCTask *plc_task;
}TaskList;                          /* 软PLC任务表模型 */

#endif
