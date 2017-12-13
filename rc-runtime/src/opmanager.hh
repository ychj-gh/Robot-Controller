#ifndef _OPMANAGER_HH_
#define _OPMANAGER_HH_

#include <native/task.h>
#include <native/event.h>
#include <native/queue.h>
#include <native/mutex.h>
#include <native/cond.h>
#include <native/timer.h>

#include <iostream>
#include <string>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "inst_type.h"
// #include "Interpolation.hh"

#include "rclinterface.h"

#include "RobotModel.h"
#include "InterpolationInterface.h"
#include "InterpolationDefault.h"
#include <memory>
using namespace RobotSpace;

extern RT_TASK              rc_manager_desc;         /* RC管理器任务描述符 */
extern RT_TASK_INFO         rc_manager_info;         /* RC管理器任务状态 */
#define RC_MANAGER_NAME     "rc_manager_task"        /* RC管理器任务名 */
#define RC_MANAGER_PRIORITY  83                      /* RC管理器任务优先级 */

extern RT_TASK              rc_interp_desc;           /* RC interp任务描述符 */
extern RT_TASK_INFO         rc_interp_info;           /* RC interp任务状态 */
#define RC_INTERP_NAME      "rc_interp_task"          /* RC interp任务名 */
#define RC_INTERP_PRIORITY  81                        /* RC interp任务优先级 */

extern RT_TASK              rc_rsi_desc;              /* RSI任务描述符 */
extern RT_TASK_INFO         rc_rsi_info;              /* RSI任务状态 */
#define RC_RSI_NAME         "rc_rsi_task"             /* RSI任务名 */
#define RC_RSI_PRIORITY     82                        /* RSI任务优先级 */

extern RT_TASK              rc_executor_desc;         /* RC执行器任务描述符 */
extern RT_TASK_INFO         rc_executor_info;         /* RC执行器任务状态 */
#define RC_EXECUTOR_NAME    "rc_executor_task"        /* RC执行器任务名 */
#define RC_EXECUTOR_PRIORITY 80                       /* RC执行器任务优先级 */

extern RT_QUEUE             mq_rc_exec_desc;          // RC解释器 消息队列描述符
#define MQ_RC_EXEC_NAME     "mq_rc_exec"              // RC解释器 消息队列名

extern RT_QUEUE             mq_rc_manager_desc;       // RC运行管理器 消息队列描述符
#define MQ_RC_MANAGER_NAME  "mq_rc_manager"           // RC运行管理器 消息队列名

extern RT_QUEUE             mq_rc_interp_desc;        // RC插补器 消息队列描述符
#define MQ_RC_INTERP_NAME   "mq_rc_interp"            // RC插补器 消息队列名

extern RT_QUEUE             mq_plc_desc;              // PLC 消息队列描述符
#define MQ_PLC_NAME         "mq_plc"                  // PLC 消息队列名

extern RT_QUEUE             mq_rc_rsi_desc;           // RSI 消息队列描述符 
#define MQ_RC_RSI_NAME      "mq_rc_rsi"               // RSI 消息队列名


extern RT_COND              inst_cond_desc;           /* 同步对象－－条件变量描述符 */
#define INST_COND_NAME      "inst_cond"
extern RT_MUTEX             inst_mutex_desc;          /* 同步对象－－互斥量描述符 */
#define INST_MUTEX_NAME     "inst_mutex"
extern RT_MUTEX             rc_mutex_desc;            /* RC与软PLC共享内存互斥量描述符　由PLC创建　RC绑定　*/

// RC运行模式
enum RcMode{
    OP_TEACH,           // 示教模式
    OP_RUN              // 再现运行模式
};

// RC运行管理器控制解释器命令
enum RcCommand{
    CMD_START,          // 开始运行
    CMD_NEXT,           // 单步运行
    CMD_RUN,            // 自动运行
    CMD_RESET,          // 返回程序起点
    CMD_INTERRUPT
    // CMD_STOP            // 停止运行
};

// RC运行状态机
enum  RcStatusMachine{
    STATUS_STOP,        // 待机态
    STATUS_READY,       // READY态，此时示教程序已完成词法、语法语义分析生成程序运行数据结构
    STATUS_AUTORUN,     // 自动运行态
    STATUS_STEP,        // 单步运行态
    STATUS_PAUSE        // 暂停态
};

// 运行管理器核心数据结构——当前RC运行状态信息数据
struct RCOperationCtrl{
    RcMode  mode;                   // RC运行模式
    bool startup;                   // 是否启动运行，0：停止    1：启动
    int stepflag;                   // 是否进行单步运行，0：非单步   1：单步step in  2:单步step over

    std::string cur_project;        // 当前工程
    std::string cur_program;        // 当前程序
    // robot_program_file_process::statement_node *exec_program_head; // 当前程序头指针
    // robot_program_file_process::statement_node *pc;     // 程序指针PC
    int cur_linenum;                    // 当前指令对应程序文件行号
    int exec_run_mode;              // 当前程序运行状态，0:待机态，1:执行态
    RcStatusMachine  status;        // RC状态机
    int interp_status;              // 0:standy, 1:run
    int prog_ready;

    int jog_mode;
    JogProc procedure;  
    int jog_startup;

    double vper;
    double aper;
    double Ts;

    int coordinate;                 // 0: joint 1: base 2: tool
public:
    RCOperationCtrl():mode(OP_TEACH), startup(0), stepflag(1),
                    cur_linenum(0),exec_run_mode(0),vper(10), aper(40),Ts(0.008),
                    jog_mode(0), coordinate(0), procedure(JOG_STOP)
    {}

};

extern RobotModel* pRobot;
// extern std::shared_ptr<RobotModel> pRobot;
// extern RobotConfig      rc_runtime_param;
// extern RobotConfig      *rc_conf;                        /*　机器人配置信息共享区指针　*/
extern RCMem            *rc_shm;                            /*　RC与软PLC共享区指针　*/
extern RCOperationCtrl  rc_core;                            /* RC核心管理器 */
extern ROBOT_INST       robot_inst_buffer_code;             // inst buffer
extern bool             robot_inst_buffer_flag ;            // inst buffer flag

extern jmp_buf          exec_startpoint;                    /* 解释执行器起点 */
extern jmp_buf          interp_startpoint;                  /* RC插补器起点 */
extern jmp_buf          rsi_startpoint;                     /* RSI实时任务起点 */


extern bool RSIStopFlag; /* THIS IS VERY IMPORTANT, WHICH CONTROL THE WHOLE LIFECYCLE OF RSI */
extern bool INRSIPeriod;
#define RSI_RUN_PERIOD   40000000   /* 160 ms */
inline void RSI_SET_STOP() { RSIStopFlag = true; }


inline bool STEPCHECK()  {
    int flag = 0;    
    // void *line ;  
    bool isfinished = true;                                    
    do{ 
        void* rc_cmd;                    /* RC控制命令 */                   
        int len = rt_queue_receive(&mq_rc_exec_desc, &rc_cmd, TM_INFINITE);   /* 等待管理器命令 */
        printf("[ received message: len=%d bytes, cmd=%d ]\n", len, *((const char *)rc_cmd));       
        char cmd = *((const char *)rc_cmd);                                               
        switch(cmd) {                                                                       
            case CMD_START:   
                flag = 0;    
                std::cout << "rc_core stratup = " << rc_core.startup << std::endl;      
                break;   
            case CMD_NEXT:   
                if(rc_core.stepflag) {
                    flag = 1;
                } else {

                }
                break;                                                                       
            case CMD_RESET:                                                                 
                rc_core.cur_linenum = 1;    
                rt_queue_flush(&mq_rc_exec_desc);                                            
                longjmp(exec_startpoint, 0);        /* 跳转至解释器起点 */                     
                break; 
            case CMD_INTERRUPT:
                isfinished = false;
                break;                                                                     
            default:                                                                    
                break;                                                                      
            }                                                                               
            rt_queue_free(&mq_rc_exec_desc, rc_cmd);            /* 释放消息内存 */       
    } while(flag || !rc_core.startup);   
    return isfinished;                                                       
}                                                                                       

inline void inst_buffer_write(ROBOT_INST &temp_inst) {
    rt_mutex_acquire(&inst_mutex_desc, TM_INFINITE); 
    robot_inst_buffer_code = temp_inst;
    robot_inst_buffer_flag = true;
    rt_cond_signal(&inst_cond_desc);
    rt_mutex_release(&inst_mutex_desc);       /* 释放同步互斥量 */
}

inline void inst_buffer_read(ROBOT_INST &temp_inst) {
    rt_mutex_acquire(&inst_mutex_desc, TM_INFINITE); 
    while(robot_inst_buffer_flag == false) {
        rt_cond_wait(&inst_cond_desc, &inst_mutex_desc, TM_INFINITE);
    }
    temp_inst = robot_inst_buffer_code;
    robot_inst_buffer_flag = false;
    rt_mutex_release(&inst_mutex_desc);       /* 释放同步互斥量 */
}

inline int send_cmd_to_rsi(int command) {
    void *cmd ;
    cmd = rt_queue_alloc(&mq_rc_rsi_desc, 1);
    (*(char*)cmd) = command;
    rt_queue_send(&mq_rc_rsi_desc, cmd, 1, Q_NORMAL);
}


inline void inst_buffer_read_nonblock(ROBOT_INST &temp_inst, bool &flag) {
    int ret;
    // rc_shm->interp_startup_flag = 0;
    // send_cmd_to_rsi(1);
    RTIME start = rt_timer_read();
    rt_mutex_acquire(&inst_mutex_desc, TM_INFINITE); 
    if(robot_inst_buffer_flag == false) {
        ret = rt_cond_wait(&inst_cond_desc, &inst_mutex_desc, 6000000);
    }
    RTIME end = rt_timer_read();
    std::cout << "read inst buffer delay = " << end-start << " ns" << endl;
    if(ret == -ETIMEDOUT) 
    {
        RSI_SET_STOP();
        flag = false;
        robot_inst_buffer_flag = false;
        send_cmd_to_rsi(2);
        std::cout << "rsi buffer time out " << std::endl;
    }
    else
    {
        temp_inst = robot_inst_buffer_code;
        robot_inst_buffer_flag = false;
        flag = true;
        send_cmd_to_rsi(1);
    }
    rt_mutex_release(&inst_mutex_desc);       /* 释放同步互斥量 */
    // rc_shm->interp_startup_flag = 1;
}

inline int send_cmd_to_exec(RcCommand command) {
    void *cmd ;
    cmd = rt_queue_alloc(&mq_rc_exec_desc, 1);
    (*(char*)cmd) = command;
    rt_queue_send(&mq_rc_exec_desc, cmd, 1, Q_NORMAL);
}


inline int send_cmd_to_interp(int command) {
    void *cmd ;
    cmd = rt_queue_alloc(&mq_rc_interp_desc, 1);
    (*(char*)cmd) = command;
    rt_queue_send(&mq_rc_interp_desc, cmd, 1, Q_NORMAL);
}

inline int rsi_waitfor_run() {
    void *request;
    rt_queue_receive(&mq_rc_rsi_desc, &request, TM_INFINITE);
    char cmd = *((const char *)request); 
    return cmd;
}

inline int interp_step(Position_ACS_deg &onepoint){
    void *request;
    rt_queue_receive(&mq_rc_interp_desc, &request, TM_INFINITE);
    char cmd = *((const char *)request); 
    switch(cmd) {
        case 1:
            pRobot->setMotorAxisPos(rc_shm,&rc_mutex_desc,onepoint);
            rt_queue_free(&mq_rc_interp_desc, request);
            break;
        case 2:
            rt_queue_free(&mq_rc_interp_desc, request);
            // Case interrupted during interpolating
            if(SHM_INTERP_START_GET(rc_shm) == 1){
                send_cmd_to_exec(CMD_INTERRUPT);
                SHM_INTERP_START_CLR(rc_shm);
                SHM_INTERP_STATUS_CLR(rc_shm);
            }
            longjmp(interp_startpoint, 0);        /* 跳转至interp起点 */    
            break;
        default:
            break;
    }

    void *msg ;
    msg = rt_queue_alloc(&mq_plc_desc, 1);
    (*(char*)msg) = 2;
    rt_queue_send(&mq_plc_desc, msg, 1, Q_NORMAL);   
}

inline int rsi_step() {
    void *request;
    rt_queue_receive(&mq_rc_rsi_desc, &request, TM_INFINITE);
    char cmd = *((const char *)request); 
    switch(cmd) {
        case 1:
            rt_queue_free(&mq_rc_rsi_desc, request);
            break;
        case 2:
            printf("RSI time out\n");
            rt_queue_free(&mq_rc_rsi_desc, request);
            RSI_SET_STOP();
            longjmp(rsi_startpoint, 0);        /* 跳转至rsi起点 */    
            break;
        default:
            break;
    }
}

int rc_core_init();                     // RC运行状态信息初始化
int interp_compute(ROBOT_INST &temp_inst);

#endif
