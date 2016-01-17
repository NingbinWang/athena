#include "delay.h"
#include "stm32f10x.h"
 int main(void)
 {	
	 	delay_init();	    	 //延时函数初始化	  
	  NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	  TIM3_PWM_Init(256,0);
	  TIM_SetCompare2(TIM3,100);	
 }

