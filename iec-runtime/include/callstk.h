#ifndef __CALLSTK_H__
#define __CALLSTK_H__

#include <stdint.h>
#include "ivalue.h"
/* 栈帧数据结构 */
typedef struct{
    uint16_t pou;       // 当前POU描述符下标
    uint32_t ret;       // 用户返回代码段地址
    uint8_t  retreg;    
    IValue   *reg;      // 寄存器组基地址
}SFrame;

/* 调用栈数据结构 */
typedef struct{
    uint16_t capacity;  // 调用栈容量
    uint16_t top;       // 栈顶下标
    SFrame *base;       // 栈基地址
}CStack;

/* 栈帧初始化 */
#define sf_init(sf, pou_id, ret_addr, regc){\
    (sf).pou = pou_id;                      \
    (sf).ret = ret_addr;                    \
    (sf).retreg = 0;                        \
    (sf).reg = new IValue[regc];            \
}

/* sf1.reg[base1 ... base1+count] <-- sf2.reg[base2 ... base1+count] */
#define sf_regcpy(sf1, base1, sf2, base2, count) { \
    for (int i = 0; i < count; i++) {              \
        (sf1).reg[base1+i] = (sf2).reg[base2+i];   \
    }                                              \
    (sf1).retreg = base2;                          \
}
/* premise: stack capacity is enough */
#define cs_push(stk, sf) {                          \
    (stk).base[(stk).top] = sf;                     \
    (stk).top++;                                    \
}
#define cs_pop(stk) {                               \
    delete[] (stk).base[(stk).top - 1].reg;         \
    (stk).top--;                                    \
}

#define fb_load(sf, fb_instance) {                  \
    for(int i = 0; i < fb_instance.size(); i ++){   \
        (sf).reg[i] = fb_instance[i];               \
    }                                               \
}       

#define fb_store(fb_instance, sf) {                 \
    for(int i = 0; i < fb_instance.size(); i ++) {  \
        fb_instance[i] = (sf).reg[i];               \
    }                                               \
}                                        

int cs_init(CStack *stk, uint16_t cap);

#endif

