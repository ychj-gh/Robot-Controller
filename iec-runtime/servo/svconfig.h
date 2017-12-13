#ifndef __SVCONFIG_H__
#define __SVCONFIG_H__

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <rtdm/rtdm.h>
#include <native/task.h>
#include <native/sem.h>
#include <native/mutex.h>
#include <native/timer.h>
#include <rtdk.h>
#include <pthread.h>


#include "ecrt.h"

// device config
#define BusCouplerPos0   0,0   // servo
#define BusCouplerPos1   0,1
#define BusCouplerPos2   0,2
#define BusCouplerPos3   0,3
#define BusCouplerPos4   0,4
#define BusCouplerPos5   0,5
#define DigitIOPos       0,6
#define ESTUN_PLC         0x0000060a,0x00000010
#define ESTUN_ProNet    0x0000060a, 0x00000001
#define NetX50          0x00000044,0x0000000f

// mode
#define MODE_PROVEL     0x03
#define MODE_PROPOS     0x01
#define MODE_CSP        0x08   

typedef struct PDO_Config
{
    int AxisNum;
    int StateR;
    unsigned int off_dig_in1;       //Statusword
    unsigned int off_dig_in2;       //Position actual value
    unsigned int off_dig_out1;      //Controlword
    unsigned int off_dig_out2;      //target position
    unsigned int off_dig_out3;      //profile velocity
    unsigned int off_dig_out4;      //end velocity
    unsigned int off_dig_out5;      //profile acceleration
    unsigned int off_dig_out6;      //profile deceleration
    unsigned int off_dig_out7;      //interpolation data position

    uint8_t *domain1_pd;
    uint8_t *domain2_pd;

    ec_domain_t *domain1;
    ec_domain_t *domain2;

    ec_domain_state_t domain1_state;
    ec_domain_state_t domain2_state;

    ec_slave_config_t *sc;
}PDO_CONFIG;

PDO_CONFIG AxisPDO[6];

///////////////////////////////////////////////////////////////////////
//                       Axis1 PDO mapped                            //
///////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A1domain1_regs[] = 
{
    {BusCouplerPos0, ESTUN_ProNet, 0x6040,0, &(AxisPDO[0].off_dig_out1)},
    {BusCouplerPos0, ESTUN_ProNet, 0x607A,0, &(AxisPDO[0].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A1domain2_regs[] =
{
    {BusCouplerPos0, ESTUN_ProNet, 0x6041,0, &(AxisPDO[0].off_dig_in1)},
    {BusCouplerPos0, ESTUN_ProNet, 0x6064,0, &(AxisPDO[0].off_dig_in2)},
    {}
};

///////////////////////////////////////////////////////////////////////
//                       Axis2 PDO mapped                            //
///////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A2domain1_regs[] = 
{
    {BusCouplerPos1, ESTUN_ProNet, 0x6040,0, &(AxisPDO[1].off_dig_out1)},
    {BusCouplerPos1, ESTUN_ProNet, 0x607A,0, &(AxisPDO[1].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A2domain2_regs[] =
{
    {BusCouplerPos1, ESTUN_ProNet, 0x6041,0, &(AxisPDO[1].off_dig_in1)},
    {BusCouplerPos1, ESTUN_ProNet, 0x6064,0, &(AxisPDO[1].off_dig_in2)},
    {}
};

///////////////////////////////////////////////////////////////////////
//                       Axis3 PDO mapped                         //
///////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A3domain1_regs[] = 
{
    {BusCouplerPos2, ESTUN_ProNet, 0x6040,0, &(AxisPDO[2].off_dig_out1)},
    {BusCouplerPos2, ESTUN_ProNet, 0x607A,0, &(AxisPDO[2].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A3domain2_regs[] =
{
    {BusCouplerPos2, ESTUN_ProNet, 0x6041,0, &(AxisPDO[2].off_dig_in1)},
    {BusCouplerPos2, ESTUN_ProNet, 0x6064,0, &(AxisPDO[2].off_dig_in2)},
    {}
};

//////////////////////////////////////////////////////////////////////////
//                       Axis4 PDO mapped                            //
//////////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A4domain1_regs[] = 
{
    {BusCouplerPos3, ESTUN_ProNet, 0x6040,0, &(AxisPDO[3].off_dig_out1)},
    {BusCouplerPos3, ESTUN_ProNet, 0x607A,0, &(AxisPDO[3].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A4domain2_regs[] =
{
    {BusCouplerPos3, ESTUN_ProNet, 0x6041,0, &(AxisPDO[3].off_dig_in1)},
    {BusCouplerPos3, ESTUN_ProNet, 0x6064,0, &(AxisPDO[3].off_dig_in2)},
    {}
};

//////////////////////////////////////////////////////////////////////////
//                       Axis5 PDO mapped                            //
//////////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A5domain1_regs[] = 
{
    {BusCouplerPos4, ESTUN_ProNet, 0x6040,0, &(AxisPDO[4].off_dig_out1)},
    {BusCouplerPos4, ESTUN_ProNet, 0x607A,0, &(AxisPDO[4].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A5domain2_regs[] =
{
    {BusCouplerPos4, ESTUN_ProNet, 0x6041,0, &(AxisPDO[4].off_dig_in1)},
    {BusCouplerPos4, ESTUN_ProNet, 0x6064,0, &(AxisPDO[4].off_dig_in2)},
    {}
};

//////////////////////////////////////////////////////////////////////////
//                       Axis6 PDO mapped                            //
//////////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t A6domain1_regs[] = 
{
    {BusCouplerPos5, ESTUN_ProNet, 0x6040,0, &(AxisPDO[5].off_dig_out1)},
    {BusCouplerPos5, ESTUN_ProNet, 0x607A,0, &(AxisPDO[5].off_dig_out2)},
    {}
};

const static ec_pdo_entry_reg_t A6domain2_regs[] =
{
    {BusCouplerPos5, ESTUN_ProNet, 0x6041,0, &(AxisPDO[5].off_dig_in1)},
    {BusCouplerPos5, ESTUN_ProNet, 0x6064,0, &(AxisPDO[5].off_dig_in2)},
    {}
};

static ec_pdo_entry_info_t slave_0_pdo_entries[] = 
{
    {0x6040,0x00,16}, /*control word*/
    {0x607A,0x00,32}, /*target position*/
    
    {0x6041,0x00,16}, /*status word*/
    {0x6064,0x00,32}, /*position actual value*/ 
};

static ec_pdo_info_t slave_0_pdos[] = 
{
    {0x1600,2,slave_0_pdo_entries + 0},
    {0x1a00,2,slave_0_pdo_entries + 2},
};

static ec_sync_info_t slave_0_syncs[] = {
    {0,EC_DIR_OUTPUT,0,NULL,EC_WD_DISABLE},
    {1,EC_DIR_INPUT,0,NULL,EC_WD_DISABLE},
    {2,EC_DIR_OUTPUT,1,slave_0_pdos + 0,EC_WD_ENABLE},
    {3,EC_DIR_INPUT,1,slave_0_pdos + 1,EC_WD_DISABLE},
    {0xff}
};


////////////Digit IO config/////////////////////////////////////////
uint8_t *IO_domain1_pd = NULL;
uint8_t *IO_domain2_pd = NULL;
ec_domain_t *IO_domain1 = NULL;
ec_domain_t *IO_domain2 = NULL;
unsigned int IO_out;
unsigned int IO_in;
ec_slave_config_t *IO_sc = NULL;
//////////////////////////////////////////////////////////////////////////
//                       Digit IO mapped                            //
//////////////////////////////////////////////////////////////////////////
const static ec_pdo_entry_reg_t IOdomain1_regs[] = 
{
    {DigitIOPos, NetX50, 0x2000,1, &IO_out},
    {}
};

const static ec_pdo_entry_reg_t IOdomain2_regs[] =
{
    {DigitIOPos, NetX50, 0x3000,1, &IO_in},
    {}
};

static ec_pdo_entry_info_t slave_IO_entries[] = 
{
    {0x2000,0x01,8},
    {0x3000,0x01,8}
    //{0x7020,0x02,16}, /* Digit Output */
    //{0x6010,0x02,16}  /* Digit Input  */
};

static ec_pdo_info_t slave_IO_pdos[] = 
{
    {0x1600,1,slave_IO_entries + 0},
    {0x1a00,1,slave_IO_entries + 1},
    //{0x1602,1,slave_IO_entries + 0},
    //{0x1a01,1,slave_IO_entries + 1},
};

static ec_sync_info_t slave_IO_syncs[] = {
    {0,EC_DIR_OUTPUT,0,NULL,EC_WD_DISABLE},
    {1,EC_DIR_INPUT,0,NULL,EC_WD_DISABLE},
    {2,EC_DIR_OUTPUT,1,slave_IO_pdos + 0,EC_WD_ENABLE},
    {3,EC_DIR_INPUT,1,slave_IO_pdos + 1,EC_WD_DISABLE},
    {0xff}
};


#endif