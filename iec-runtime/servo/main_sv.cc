#include <sys/mman.h> /* required for mlockall() */
#include <sys/socket.h>
#include <netdb.h>
#include <native/task.h>
#include <native/heap.h>
#include <unistd.h> /* required for pause() */
#include <signal.h>
#include <stdlib.h>

#include "mq.h"
#include "servo.h"
#include "io.h"
#include "logger.h"
#include "svconfig.h"
#undef LOGGER_LEVEL
#define LOGGER_LEVEL LEVEL_ERR

#define AXISCOUNT     6

RT_TASK sv_task;            /* 伺服任务描述符 */
RT_HEAP sv_heap_desc;       /* 伺服映像数据共享区描述符 */
RT_HEAP svconf_heap;        /* 伺服配置共享区描述符 */

RT_MUTEX sv_mutex_desc;     /* 伺服共享区同步对象描述符 */

ServoConfig *sv_conf;       /* 伺服配置共享区指针 */
SVMem *sv_shm;              /* 伺服映像数据共享区指针 */

RT_HEAP ioconf_heap;
IOConfig *io_conf;
IOMem io_shm;

unsigned int Din;

#define dump_servo_conf(config) {\
    LOGGER_DBG(DFLAG_LONG, "Received ServoConfig:\n .axis_count = %d\n .update_interval = %d",\
        config.axis_count, config.update_interval); \
}
#define dump_axis_conf(config) {\
    LOGGER_DBG(DFLAG_SHORT,\
            "Received AxisConfig:\n .name = %s\n .id = %d\n .type = %d\n .combined = %d\n .opmode = %d\n"\
            " .min_pos = %f\n .max_pos = %f\n .max_vel = %f\n .max_acc = %f\n .max_dec = %f\n .max_jerk = %f",\
            config.name, config.id, config.type, config.combined, config.opmode,\
            config.min_pos, config.max_pos, config.max_vel, config.max_acc, config.max_dec, config.max_jerk);\
}


// ethercat master object
static ec_master_t *master = NULL;
//static ec_master_state_t master_state = {};

// 角度与编码器数值转换
long int Deg2Encode(double degree)
{
    return (long int) 131072 * degree / 360.0;
}

double Encode2Deg(long int pos)
{
    return (double)(pos) / 131072.0 * 360.0;
}

// 进入伺服上电状态
void Enable_Operation(int cyc, PDO_CONFIG *Axis_PDO)
{
    if(cyc == 1)
        EC_WRITE_U16(Axis_PDO->domain1_pd + Axis_PDO->off_dig_out1,0x06);
    else if(cyc == 2)
        EC_WRITE_U16(Axis_PDO->domain1_pd + Axis_PDO->off_dig_out1,0x07);
    else if(cyc == 3)
    {
        EC_WRITE_U16(Axis_PDO->domain1_pd + Axis_PDO->off_dig_out1,0x0f);
        for(int i = 0; i < AXISCOUNT; ++i)
            EC_WRITE_U32(AxisPDO[i].domain1_pd + AxisPDO[i].off_dig_out2, Deg2Encode(sv_shm->axis_data[i].actual_pos));
    }
}

/* realtime context */
static void servo_update(void *cookie) {

    sv_conf_bind(&svconf_heap, &sv_conf);   /* 绑定伺服配置共享区 */
    dump_servo_conf((*sv_conf));
    sv_mem_bind(sv_shm, sv_conf);           /* 绑定伺服数据共享区 */
    sv_syncobj_bind(&sv_mutex_desc, SV_MUTEX_NAME); /* 绑定同步对象 */

    io_conf_bind(&ioconf_heap, &io_conf);
    io_mem_bind(&io_shm, io_conf);
    dump_io_conf(io_conf);
    LOGGER_DBG(DFLAG_LONG, "I/O Shared Memory:\n .total_size = %d\n .diu_size = %d\n .dou_size = %d\n .aiu_size = %d\n .aou_size = %d",
    IO_SHM_SIZE(io_conf), DIU_SIZE(io_conf), DOU_SIZE(io_conf), AIU_SIZE(io_conf), AOU_SIZE(io_conf));


    ec_slave_config_state_t A1_state;
    uint8_t control_count = 0;
    uint8_t OutRange_flag = 0;

    // servo_mocker_init();                     /* 初始化伺服模拟器，主要用来建立TCP连接 */
    printf("start servo update\n");

    rt_task_set_periodic(NULL, TM_NOW, sv_conf->update_interval);
    while (1) {
        rt_task_wait_period(NULL);
        ecrt_master_receive(master);
        for(int i = 0; i < AXISCOUNT; ++i)
        {
        ecrt_domain_process(AxisPDO[i].domain1);
        ecrt_domain_process(AxisPDO[i].domain2);
        }
        ecrt_domain_process(IO_domain1);
        ecrt_domain_process(IO_domain2);

        ecrt_slave_config_state(AxisPDO[0].sc, &A1_state);

        // control_count 计数用于发3条指令进入伺服上电状态 opflag 置 1 时开始将位置数据写入伺服
        //if(opflag == 0 && A1_state.operational) control_count++;
        //if(control_count > 3)   {control_count = 3; opflag = 1;}   
        if(A1_state.operational)  control_count++;
        if(control_count >=4 )     {
            control_count = 4; 
            sv_shm->ctrl_area.status_word = 1;
        } 
        if(control_count > 0) 
        { 
            Din = EC_READ_U8(IO_domain2_pd + IO_in);
            if(Din & (1<<2))
                io_shm.base[0][0] = 0x01;
            else 
                io_shm.base[0][0] = 0x00;
            // printf("%d\n",Din);
            for(int i = 0; i < AXISCOUNT; ++i)
                sv_shm->axis_data[i].actual_pos = Encode2Deg(EC_READ_U32(AxisPDO[i].domain2_pd + AxisPDO[i].off_dig_in2));
            sv_shm->status_area[0].status_word = EC_READ_U16(AxisPDO[0].domain2_pd + AxisPDO[0].off_dig_in1);
        }
        switch(sv_shm->ctrl_area.control_word) {
        case SERVO_RUN:
                // if(opflag == 0)
                // printf("%d\n",Din);
                // for(int i = 0; i < 6; i ++) {
                //     printf("servo %d : %lf   ", i, sv_shm->axis_data[i].command_pos);
                // }
                // printf("\n\n");
                
                if(control_count <= 3) 
                    for(int i = 0; i < AXISCOUNT; ++i)
                    {
                        OutRange_flag = 0;
                        Enable_Operation(control_count,&AxisPDO[i]);
                    }
                else if(sv_shm->data_status == DATA_NEW)
                {
                    // fprintf(stderr, "data new\n");
                    // printf("command pos: ");
                    for(int i = 0; i < AXISCOUNT; ++i)
                    {   
                        // 每次发送一次位置值需要发送控制字 0x0f
                        if(OutRange_flag == 0 && fabs(sv_shm->axis_data[i].command_pos - sv_shm->axis_data[i].actual_pos) < 1)  // < 4 degree
                        {
                            EC_WRITE_U32(AxisPDO[i].domain1_pd + AxisPDO[i].off_dig_out2, Deg2Encode(sv_shm->axis_data[i].command_pos));
                            EC_WRITE_U16(AxisPDO[i].domain1_pd + AxisPDO[i].off_dig_out1, 0x0f);
                            // printf(" %lf ",sv_shm->axis_data[i].command_pos);
                        }
                        else
                        {   
                            OutRange_flag = 1;
                            printf("commond Pos %lf %lf %lf %lf %lf %lf\n",sv_shm->axis_data[0].command_pos
                                                                        ,sv_shm->axis_data[1].command_pos
                                                                        ,sv_shm->axis_data[2].command_pos
                                                                        ,sv_shm->axis_data[3].command_pos
                                                                        ,sv_shm->axis_data[4].command_pos
                                                                        ,sv_shm->axis_data[5].command_pos);
                            printf(" actual Pos %lf %lf %lf %lf %lf %lf\n",sv_shm->axis_data[0].actual_pos
                                                                        ,sv_shm->axis_data[1].actual_pos
                                                                        ,sv_shm->axis_data[2].actual_pos
                                                                        ,sv_shm->axis_data[3].actual_pos
                                                                        ,sv_shm->axis_data[4].actual_pos
                                                                        ,sv_shm->axis_data[5].actual_pos);                
                            printf("*************************************************************\n");
                            printf("*********************** Out of Range! ***********************\n");
                            printf("*************************************************************\n");
                        }
                    }
                    // printf("\n");
                    sv_shm->data_status = DATA_OUT_OF_TIME;
                }

            break;
        case SERVO_STOP:
                for(int i = 0; i < AXISCOUNT; ++i)
                    EC_WRITE_U16(AxisPDO[i].domain1_pd + AxisPDO[i].off_dig_out1, 0x06);
                control_count = 0;
                sv_shm->data_status = DATA_OUT_OF_TIME;
                sv_shm->ctrl_area.status_word = 0;
            break;
        }
        for(int i = 0; i < AXISCOUNT; ++i)
        {
            ecrt_domain_queue(AxisPDO[i].domain1);
            ecrt_domain_queue(AxisPDO[i].domain2);
        }
        ecrt_domain_queue(IO_domain1);
        ecrt_domain_queue(IO_domain2);
        ecrt_master_send(master);
    }
}


/***************************************************************************************/
// Configure each Axis's PDO domains
// @Axis_PDO                : select one Axis to configure
// @pdo_entry_regs1         : mapped array
// @pdo_entry_regs2         :
// @vendor_id & produce_code: use macro definition
// return                   : if no error return 0; else return -1;
// 2016/9/14                  ychj
/***************************************************************************************/
int PDO_Configuration(PDO_CONFIG *Axis_PDO, const ec_pdo_entry_reg_t *pdo_entry_regs1,\
                                            const ec_pdo_entry_reg_t *pdo_entry_regs2,\
             uint16_t alias,uint16_t position,uint32_t vendor_id,uint32_t product_code)
{
    Axis_PDO->domain1 = ecrt_master_create_domain(master);
    if(!Axis_PDO->domain1)  return -1;
    Axis_PDO->domain2 = ecrt_master_create_domain(master);
    if(!Axis_PDO->domain2)  return -1;
    printf("Creating servo %d configurations...\n",Axis_PDO->AxisNum);

    Axis_PDO->sc = ecrt_master_slave_config(master,alias,position,vendor_id,product_code);
    if(!Axis_PDO->sc)
    {
        fprintf(stderr,"Failed to get servo %d configuration.\n",Axis_PDO->AxisNum);
        return -1;
    }

    printf("Configuring servo %d PDOS...\n",Axis_PDO->AxisNum);
    if(ecrt_slave_config_pdos(Axis_PDO->sc,EC_END,slave_0_syncs))
    {
        fprintf(stderr, "Failed to configure servo %d PDOs.\n",Axis_PDO->AxisNum);
        return -1;
    }
    if (ecrt_domain_reg_pdo_entry_list(Axis_PDO->domain1, pdo_entry_regs1))
    {
        printf("Servo %d PDO entry registration failed!\n",Axis_PDO->AxisNum);
        return -1;
    }
    if (ecrt_domain_reg_pdo_entry_list(Axis_PDO->domain2, pdo_entry_regs2))
    {
        printf("Servo %d PDO entry registration failed!\n",Axis_PDO->AxisNum);
        return -1;
    }
    return 0;
}

void sig_handler(int signo) {
    LOGGER_DBG(DFLAG_SHORT, "Servo Driver Received Signal: %d", (int)signo);
    if (signo == SIGUSR1) {
        if (rt_heap_delete(&sv_heap_desc) < 0) {
            LOGGER_ERR(E_HEAP_DELETE, "");
        }
        sv_conf_unbind(&svconf_heap);
        if (rt_task_delete(&sv_task) < 0) {
            LOGGER_ERR(E_SVTASK_DELETE, "");
        }
        exit(0);
    }
}
/* non-realtime context */
int main() {
    mlockall(MCL_CURRENT|MCL_FUTURE);

    /* set signal handler */
    if (signal(SIGUSR1, &sig_handler) == SIG_ERR) {
        LOGGER_ERR(E_SIG_SVKILL, "");
    }

    for(int i = 0; i < AXISCOUNT; ++i) {
        AxisPDO[i].AxisNum = i + 1;
        AxisPDO[i].domain1_pd = NULL;
        AxisPDO[i].domain2_pd = NULL;
        AxisPDO[i].domain1 = NULL;
        AxisPDO[i].domain2 = NULL;
    }

    // 模式选择参数
    uint8_t data[4] = {0x03,0x01,0x08,0x07};
    // 6轴减速比参数
    uint8_t numerator[6][4] = {{0x73,0x00,0x00,0x00},    // 115
                                  {0x73,0x00,0x00,0x00},     // 115
                                  {0x73,0x00,0x00,0x00},     // 115
                                  {0x1e,0x00,0x00,0x00},     //30
                                  {0x2f,0x14,0x00,0x00},     //5167
                                  {0x32,0x00,0x00,0x00}      //50
                                  };

    uint8_t divisor[6][4] = { {0x01,0x00,0x00,0x00},      //1
                                 {0x01,0x00,0x00,0x00},      //1
                                 {0x01,0x00,0x00,0x00},      // 1
                                 {0x01,0x00,0x00,0x00},      // 1
                                 {0x64,0x00,0x00,0x00},      //100
                                 {0x01,0x00,0x00,0x00}       // 1
                                 };

   // 6轴位置极限参数
    uint8_t softposmax[6][4] = {{0x00,0x00,0x01,0x00},    // 65536   180du
                                {0x8e,0xe3,0x00,0x00},   // 58254   160du
                                {0xc7,0x71,0x00,0x00},   // 29127    80du
                                {0xc7,0xf1,0x00,0x00},   // 61895   170du
                                {0x00,0xc0,0x00,0x00},   // 49152   135du
                                {0x00,0x00,0x02,0x00},   // 131072  360du
                                };

    uint8_t softposmin[6][4] = {{0x01,0x00,0xff,0xff},   // -65535  -180du 
                                {0x72,0x9c,0xff,0xff},  // -25486  -70du
                                {0x8f,0xe3,0xfe,0xff},  // -72817  -200du
                                {0x39,0x0e,0xff,0xff},  // -61895  -170du
                                {0x00,0x40,0xff,0xff},  // -49152  -135du
                                {0x00,0x00,0xfe,0xff},  // -131072 -360du 
                                };

    printf("Requesting master...\n");
    master = ecrt_request_master(0);
    if (!master) return -1;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///     PDO Configuration
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Axis1
    if(PDO_Configuration(&AxisPDO[0],A1domain1_regs,A1domain2_regs,BusCouplerPos0,ESTUN_ProNet))
        return -1;
    // Axis2
    if(PDO_Configuration(&AxisPDO[1],A2domain1_regs,A2domain2_regs,BusCouplerPos1,ESTUN_ProNet))
        return -1;
    // Axis3
    if(PDO_Configuration(&AxisPDO[2],A3domain1_regs,A3domain2_regs,BusCouplerPos2,ESTUN_ProNet))
        return -1;
    // Axis4
    if(PDO_Configuration(&AxisPDO[3],A4domain1_regs,A4domain2_regs,BusCouplerPos3,ESTUN_ProNet))
        return -1;
    // Axis5
    if(PDO_Configuration(&AxisPDO[4],A5domain1_regs,A5domain2_regs,BusCouplerPos4,ESTUN_ProNet))
        return -1;
    // Axis6
    if(PDO_Configuration(&AxisPDO[5],A6domain1_regs,A6domain2_regs,BusCouplerPos5,ESTUN_ProNet))
        return -1;

    // Distributed Clock
    for(int i = 0; i < AXISCOUNT; ++i)
        ecrt_slave_config_dc(AxisPDO[i].sc,0x0300,1000000,0,1000000,0);

    // Digit IO PDO domain 
    if(!(IO_domain1 = ecrt_master_create_domain(master)))
        return -1;
    if(!(IO_domain2 = ecrt_master_create_domain(master)))
        return -1;
    if(!(IO_sc = ecrt_master_slave_config(master,DigitIOPos,NetX50)))
         return -1;
    // if(ecrt_slave_config_pdos(IO_sc,EC_END,slave_IO_syncs))
    //      return -1;
    if(ecrt_domain_reg_pdo_entry_list(IO_domain1, IOdomain1_regs))
        return -1;
    if(ecrt_domain_reg_pdo_entry_list(IO_domain2, IOdomain2_regs))
        return -1;

    ecrt_slave_config_dc(IO_sc,0x0300,1000000,0,1000000,0);
    
    // 使用 SDO 进行配置运行模式、减速比、极限位置    
    for(int i = 0; i < AXISCOUNT; ++i)      /// 4 Axis
    {
        uint32_t abortcode;
        ecrt_master_sdo_download(master,i,0x6060,0,&data[2],1,&abortcode);    //csp mode
        // Axis ratio set //
        ecrt_master_sdo_download(master,i,0x6093,1,numerator[i],4,&abortcode);
        ecrt_master_sdo_download(master,i,0x6093,2,divisor[i],4,&abortcode);
        // software position limit
        ecrt_master_sdo_download(master,i,0x607d,1,softposmin[i],4,&abortcode);
        ecrt_master_sdo_download(master,i,0x607d,2,softposmax[i],4,&abortcode);
    }


    printf("Activating master...\n");
    if(ecrt_master_activate(master))
        return -1;

    for(int i = 0; i < AXISCOUNT; ++i)
    {
        if(!(AxisPDO[i].domain1_pd = ecrt_domain_data(AxisPDO[i].domain1)))
            return -1;
        if(!(AxisPDO[i].domain2_pd = ecrt_domain_data(AxisPDO[i].domain2)))
            return -1;
    }

    // Digit IO domain_pd
    if(!(IO_domain1_pd = ecrt_domain_data(IO_domain1)))
        return -1;
    if(!(IO_domain2_pd = ecrt_domain_data(IO_domain2)))
        return -1;
    /* start servo rt task */
    if (rt_task_create(&sv_task, SV_TASK_NAME, 0, SV_TASK_PRIORITY, 0) < 0) {
        LOGGER_ERR(E_SVTASK_CREATE, "");
    }
    if (rt_task_start(&sv_task, &servo_update, (void *)0) < 0) {
        LOGGER_ERR(E_SVTASK_START, "");
    }
    pause();

    return 0;
}
