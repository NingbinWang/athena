#include "delay.h"
#include "stm32f10x.h"
#include "timer.h"
#include "MPU6050.h"
#include "usart.h"
 int main(void)
 {	
	  int mpu6050flag;
	  u16 times=0;
	 	delay_init();	    	 //��ʱ������ʼ��	  
	  NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 
	  TIM3_PWM_Init(256,0);
	  TIM_SetCompare2(TIM3,100);	
	  TIM4_PWM_Init(256,0);
	  TIM_SetCompare2(TIM4,100);
	  //init uart+++
	  uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	 printf("tianya\n");
	  while(1){
			times++;
			if(times%200==0)printf("hello world\n");
			delay_ms(10);
			MPU6050_Initialize();
		}
	 
 }

