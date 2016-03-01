#include "wifi.h"

void WIFI_PowerOn(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;				 //PB13 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.13
 GPIO_SetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_12);						 //GPIOB.13输出高
}