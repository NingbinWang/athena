/*
�ɿ�athena������
���ߣ�alex wang 
���䣺samuel_wnb@live.com
˵����
I2C PA9 SCL PA10 SDA ��������mpu6050
*/
#include "sysconfig.h"
#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "wifi.h"

//==========================================================
//��������
//==========================================================
 bool mpu6050_status;
//==========================================================
 int main(void)
 {	
	 //<alex-20160228> init uart++++
	    NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	    uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	 #ifdef USBDEBUG
	    printf("[athena]usart is ok\r\n");
	 #endif
	 //<alex-20160228> init uart----
	 delay_init(); //delay������ʼ��
	 //<alex-20160228>��ʼ��mpu6050I2C+++++
	 MPU6050_I2C_Init();
	 mpu6050_status = MPU6050_TestConnection();
	 if(mpu6050_status == TRUE){
	 MPU6050_Initialize();
   }else{
		 #ifdef USBDEBUG
		    printf("mpu6050 is not here\r\n");
		 #endif
		 return -1;
	 }
	 //<alex-20160228>��ʼ��mpu6050I2C-----
	 LED_Init(); //��ʼ��LED
	 MotorInit();//HOW TO TEST
	 #ifdef MOTOR_TEST
	     MotorPwmFlash(100,200,300,400);
	 #endif
	 #ifdef USBDEBUG
	     printf("Motor init ok!\r\n");
	 #endif
	 
	 /**********************************************
	 ���������
	 ***********************************************/
	 LED1 = 0;
	 LED2 = 0;
	 LED3 = 0;
	 LED4 = 0;
	 while(1)
	 {
		 printf("[athena]start\r\n");
		 printf("mpu6050 %s\r\n",mpu6050_status? "true":"flase");
		 delay_ms(1000);
	 }
	 return 0;
 }

