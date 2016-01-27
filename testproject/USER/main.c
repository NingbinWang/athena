#include "delay.h"
#include "stm32f10x.h"
#include "timer.h"
#include "MPU6050.h"
#include "usart.h"
 int main(void)
 {	
	  int mpu6050flag;
	  u16 times=0;
	 	delay_init();	    	 //延时函数初始化	  
	  NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 
	  TIM3_PWM_Init(256,0);
	  TIM_SetCompare2(TIM3,100);	
	  TIM4_PWM_Init(256,0);
	  TIM_SetCompare2(TIM4,100);
	  //init uart+++
	  uart_init(9600);	 //串口初始化为9600
	 printf("tianya\n");
	  while(1){
			times++;
			if(times%200==0)printf("hello world\n");
			delay_ms(10);
			MPU6050_Initialize();
		}
	 
 }

