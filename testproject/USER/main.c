#include "delay.h"
#include "stm32f10x.h"
 int main(void)
 {	
	 	delay_init();	    	 //��ʱ������ʼ��	  
	  NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  TIM3_PWM_Init(256,0);
	  TIM_SetCompare2(TIM3,100);	
 }

