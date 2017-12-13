#include "callstk.h"
#include "../../include/syslimit.h"
#include "../../include/logger.h"

int cs_init(CStack *stk, uint16_t cap) {
    assert(stk != NULL);
    assert(cap <= MAX_CS_CAP); /* guaranteed by verifier */

    stk->capacity = cap+1;
    stk->top = 1; /* MUST be 1(reduce bound case for main()) */
    stk->base = new SFrame[stk->capacity];
    if (stk->base == NULL) {
        LOGGER_ERR(E_OOM, "initializing calling stack");
    }
    return 0;
}
