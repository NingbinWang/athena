#include "led.h"
/********************************************
              Led��ʼ��
function:
1.����LED�ӿڷ���
2.����LED���п���ģʽ
Led interface:
Led1-->PA8
Led2-->PA11
Led3-->PB6
Led4-->PB7

********************************************/
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PB�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;				 //LED1-->PA.11 LED2-->PA.12 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.11 GPIO.12
 GPIO_SetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_11);						 //GPIOA.11 GPIO.12 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	    		 //LED3-->PB.5 LED3-->PB.6 �˿�����, �������
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7); 						 //PB.5 PB.6 ����� 
}
 