#include "led.h"
/********************************************
              Led初始化
function:
1.设置LED接口方向
2.设置LED所有开机模式
Led interface:
Led1-->PA8
Led2-->PA11
Led3-->PB6
Led4-->PB7

********************************************/
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PB端口时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;				 //LED1-->PA.11 LED2-->PA.12 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.11 GPIO.12
 GPIO_SetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_11);						 //GPIOA.11 GPIO.12 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	    		 //LED3-->PB.5 LED3-->PB.6 端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7); 						 //PB.5 PB.6 输出高 
}
 