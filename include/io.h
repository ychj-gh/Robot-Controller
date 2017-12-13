#ifndef __IO_H__
#define __IO_H__

#include <native/heap.h>
#include <stdint.h>
#include "logger.h"

#define MAX_IO_NAME_SIZE 			10
#define MIN_IO_INTERVAL				2000000 /* 单位ns */
#define MAX_IO_CHANNELS				16		/* 每一种IO最多的通道数*/

// typedef struct{
// 	char name[MAX_IO_NAME_SIZE];											 	
// 	uint8_t datatype;						/* I/O设备类型 */						
// }IODevice;

typedef struct{
	char name[MAX_IO_NAME_SIZE];											 	
	uint8_t datatype;						/* I/O设备类型 */	
	uint8_t iotype;							/* 输入输出类型 */
	uint8_t pid;							/* 设备总线地址编号 */
	uint8_t id[MAX_IO_CHANNELS];			/* ID 0-15数字 | 16-31模拟*/
	uint8_t size;							/* I/O端口数目 */
}IOMap;

/*-----------------------------------------------------------------------------
 * I/O Configuration
 *---------------------------------------------------------------------------*/
#define IO_TYPE_COUNT 				8
typedef struct{
	uint32_t update_interval;				/* I/O 数据刷新周期 */
	uint8_t  typecount;						/* 不同IO类型的个数*/
	IOMap	 io_map[IO_TYPE_COUNT];			/* id 映射关系 */
}IOConfig;

#define IO_CONFIG_SIZE 		(sizeof(IOConfig))
#define IO_CONFIG_NAME 		"io_conf"
/*-----------------------------------------------------------------------------
 * I/O Shared Memory Structure
 *---------------------------------------------------------------------------*/
// IO 数据映像区
#define BLOCK_COUNT					2
typedef struct{
	RT_HEAP heap[BLOCK_COUNT];				/* IO 数据区分配堆内存描述符 */
	char *base[BLOCK_COUNT];				/* IO 数据分配堆基地址（输入|输出） */				
}IOMem;
static const char* io_heap_name[] = {"IO_Mem_Input", "IO_Mem_Output"};

/********************************************************************************/
/* 数字I/O 一个端口 1bit,８个端口一个数字I/O通道
/*　模拟I/O 一个端口　32bit, 8　个端口一个模拟I/O通道
/* 数字IO,模拟IO,输入输出各有16个通道
/********************************************************************************/
#define DIGIT_CHANNELS 				16
#define ANALOG_CHANNELS				16
#define ANALOGPORT_SIZE				4										// 32bit　1个模拟IO端口大小（字节）
#define DIGITUNIT_SIZE				1										// 8bit 1个数字IO通道大小（字节　１bit*8）
#define ANALOGUNIT_SIZE				(ANALOGPORT_SIZE*8)						// 1　个模拟IO通道大小（字节　4bytes*8）
#define DIGIT_SIZE					(DIGITUNIT_SIZE*DIGIT_CHANNELS)			// 数字IO输入（输出）总字节数			
#define ANALOG_SIZE 				(ANALOGUNIT_SIZE*ANALOG_CHANNELS) 		// 模拟IO输入（输出）总字节数
#define IOMEM_HEAP_SIZE				(2*(DIGIT_SIZE+ANALOG_SIZE))			// IO共享内存的总大小（字节）

#define DIGIT_IO					0
#define ANALOG_IO					1
#define INPUT_IO					0
#define OUTPUT_IO					1

#define LDI(iomem)					(iomem.base[0])
#define LAI(iomem)					(iomem.base[0]+DIGIT_SIZE)
#define LDO(iomem)					(iomem.base[1])
#define LAO(iomem)					(iomem.base[1]+DIGIT_SIZE)
#define RDI(iomem)
#define RDO(iomem)
#define RAI(iomem)
#define RAO(iomem)

// 要改　！！！！
/*-----------------------------------------------------------------------------
 * Digital I/O Unit Operation Macros
 * I/O data is stored in Ivalue.v.value_u (type IUInt)
 *---------------------------------------------------------------------------*/
#undef MASK1
#define MASK1(p,n)	((~((~(IUInt)0)<<(n)))<<(p)) //置从位置p开始的n个bit为１
#undef MASK0
#define MASK0(p,n)	(~MASK1(p,n))
#define RES(num, shift) ((num) & MASK1(0,shift)) /* get residue */

/**
 * pos：通道号，　size：表示位数
 */
// #define SHIFT 3 /* 8 = 2^3; 8 is the bit width of IOMem.diu */
// #define BASE(base, pos) (*(IUInt*)&(base)[(pos)>>SHIFT]) /* MUST dereference first, then cast type!! */
// #define getdch(diu, pos, size) ((BASE(diu,pos) >> RES(pos,SHIFT)) & MASK1(0,size))
// #define setdch(dou, pos, size, value) {                                                       \
//     BASE(dou,pos) = BASE(dou,pos) & MASK0(RES(pos,SHIFT), size) | ((value)<<RES(pos, SHIFT)); \
// }
#define BASE(base,pos) (*(IUInt*)&base[(pos)])
#define getdch(diu,pos,size) ((BASE(diu,pos)) & MASK1(0,size))
#define setdch(dou,pos,size,value) {			\
	BASE(dou,pos) = BASE(dou,pos) & MASK0(0,size) | (value);\
}while(0)
/*-----------------------------------------------------------------------------
 * Analog I/O Unit Operation Macros
 *---------------------------------------------------------------------------*/
#define getach(aiu, iuint, ich) (*(uint32_t*)&(aiu)[(iuint-16)*ANALOGUNIT_SIZE+ich*ANALOGPORT_SIZE])
//TODO!!!
#define setach(aou, iuint, ich, value) //{aou[iuint*AU_CHANNELS+ich] = value;}


/*-----------------------------------------------------------------------------
 * I/O Config Shared Memory Operation Funcions
 *---------------------------------------------------------------------------*/
inline void io_conf_create(RT_HEAP *heap, IOConfig **conf){
	if(rt_heap_create(heap,IO_CONFIG_NAME,IO_CONFIG_SIZE,H_SHARED) < 0)
		LOGGER_ERR(E_HEAP_CREATE, "(name = %s, size = %d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
	if(rt_heap_alloc(heap,IO_CONFIG_SIZE,TM_INFINITE,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name = %s, size = %d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
}

inline void io_conf_bind(RT_HEAP *heap, IOConfig **conf){
	if(rt_heap_bind(heap,IO_CONFIG_NAME, TM_INFINITE) < 0)
		LOGGER_ERR(E_HEAP_BIND, "(name = %s, size = %d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
	if(rt_heap_alloc(heap,0,TM_NONBLOCK,(void **)conf) < 0)
		LOGGER_ERR(E_HEAP_ALLOC, "(name = %s, size = %d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
}

inline void io_conf_unbind(RT_HEAP *heap){
	if(rt_heap_unbind(heap) < 0)
		LOGGER_ERR(E_HEAP_UNBIND, "(name=%s, size=%d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
}

inline void io_conf_delete(RT_HEAP *heap){
	if(rt_heap_delete(heap) < 0)
		LOGGER_ERR(E_HEAP_DELETE, "(name=%s, size=%d)", IO_CONFIG_NAME, IO_CONFIG_SIZE);
}

/*---------------------------------------------------------------------
 * I/O shared memory operation functions
 *---------------------------------------------------------------------*/
#define M_LOCAL 	1
#define M_SHARED	2
inline void io_mem_create(IOMem *iomem, int mode){
	int io_size[BLOCK_COUNT] = {DIGIT_SIZE+ANALOG_SIZE, DIGIT_SIZE+ANALOG_SIZE};
	if(M_LOCAL == mode){
		for(int i = 0; i < BLOCK_COUNT; ++i){
			if((iomem->base[i] = new char[io_size[i]]) == NULL)
				LOGGER_ERR(E_OOM, "initializing iomem(Mode = M_LOCAL)");
			else 
				LOGGER_DBG(DFLAG_LONG,"iomem created success");
		}
	}else if(M_SHARED == mode){
		int ret;
		for(int i = 0; i < BLOCK_COUNT; ++i){
			if(ret = rt_heap_create(&iomem->heap[i],io_heap_name[i],io_size[i],H_SHARED) < 0)
				LOGGER_ERR(E_HEAP_CREATE, "(name = %s, size = %d, ret = %d)", io_heap_name[i], io_size[i], ret);
			if(ret = rt_heap_alloc(&iomem->heap[i],io_size[i],TM_INFINITE,(void **)&iomem->base[i]) < 0)
			 	LOGGER_ERR(E_HEAP_ALLOC, "(name = %s, size = %d, ret = %d)", io_heap_name[i], io_size[i], ret);
		}
	}
	memset(iomem->base[0],0,IOMEM_HEAP_SIZE);								// 初始均为0
}

inline void io_mem_bind(IOMem *iomem){
	for(int i = 0; i < BLOCK_COUNT; ++i){
		if(rt_heap_bind(&iomem->heap[i], io_heap_name[i],TM_INFINITE) < 0)
			LOGGER_ERR(E_HEAP_BIND, "(name=%s)", io_heap_name[i]);
		if(rt_heap_alloc(&iomem->heap[i],0,TM_NONBLOCK, (void **)&iomem->base[i]) < 0)
			LOGGER_ERR(E_HEAP_ALLOC, "(name=%s)", io_heap_name[i]);
	}
}

inline void io_mem_unbind(IOMem *iomem){
	for(int i = 0; i < BLOCK_COUNT; ++i)
		if(rt_heap_unbind(&iomem->heap[i]) < 0)
			LOGGER_ERR(E_HEAP_UNBIND, "(name=%s)", io_heap_name[i]);
}
// TODO delete local
inline void io_mem_delete(IOMem *iomem){
	for(int i = 0; i < BLOCK_COUNT; ++i)
		if(rt_heap_delete(&iomem->heap[i]) < 0)
			LOGGER_ERR(E_HEAP_DELETE, "(name=%s)", io_heap_name[i]);
}

inline void io_mem_cpy(IOMem *mem1, IOMem *mem2){
	memcpy(mem1->base[0],mem2->base[0],IOMEM_HEAP_SIZE);
}
#endif