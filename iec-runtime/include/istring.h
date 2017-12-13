#ifndef __ISTRING_H__
#define __ISTRING_H__

#include <stdint.h>

typedef struct{
	uint32_t size;		/* 字符串池容量 */
	uint32_t index;		/* 空闲空间起始索引 */
	char* base;			/* 字符串池基地址 */
}StrPool;

int sp_init(StrPool *sp, uint32_t size);
char *sp_add(StrPool *sp, const char *str, uint32_t size);
void sp_clean(StrPool *sp);

#endif
