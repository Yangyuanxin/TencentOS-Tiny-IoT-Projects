#include "delay.h"
#include "sys.h"	    

//延时nus
//nus为要延时的us数.	
//nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)	 

//延时nms
//nms:要延时的ms数

void delay_us(uint32_t time_us) {
  uint32_t clk = 80;               // CPU 4MHz
  uint32_t ticks = time_us * clk;  // time is us
  uint32_t told = SysTick->VAL;
  uint32_t tnow = told;
  uint32_t tcnt = 0;
  for(; tcnt<ticks; tnow=SysTick->VAL)
  {
    if(tnow != told) {
      if(tnow < told) {
        tcnt += told - tnow;
      } else { 
        tcnt += SysTick->LOAD-tnow + told;
      } told = tnow;
    }
  }
}

void delay_ms(uint32_t time_ms) {
  uint32_t clk = 80;               // CPU 4MHz
  uint32_t ticks = time_ms * clk * 1000;  // time is ms
  uint32_t told = SysTick->VAL;
  uint32_t tnow = told;
  uint32_t tcnt = 0;
  for(; tcnt<ticks; tnow=SysTick->VAL)
  {
    if(tnow != told) {
      if(tnow < told) {
        tcnt += told - tnow;
      } else { 
        tcnt += SysTick->LOAD-tnow + told;
      } told = tnow;
    }
  }
}

			 



































