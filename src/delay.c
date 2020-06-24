#include "delay.h"

#define CPU_Freeq 64000000

void delayInit(void){
    SCB_DEMCR |= 0x01000000;
    DWT_CYCCNT  = 0;
	DWT_CONTROL |= 1;
}

void _delay_loop(uint32_t loop){
    uint32_t t0 =  DWT_CYCCNT;
    while (DWT_CYCCNT-t0 < loop);
}

void _delay_us(uint32_t us){
    uint32_t t0 =  DWT_CYCCNT;
    uint32_t count =  us * (CPU_Freeq/1000000)-49;
    while (DWT_CYCCNT-t0 < count);
}

void _delay_ms(uint32_t ms){
    uint32_t t0 =  DWT_CYCCNT;
    uint32_t count =  ms * (CPU_Freeq/1000)-41;
    while (DWT_CYCCNT-t0 < count);
}



