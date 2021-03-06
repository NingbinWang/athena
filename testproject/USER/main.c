/*
飞控athena主程序
作者：alex wang 
邮箱：samuel_wnb@live.com
说明：
I2C PA9 SCL PA10 SDA 用于连接mpu6050
*/
#include "system.h"
//==========================================================
//变量集合
//==========================================================
 bool mpu6050_status;

//==========================================================
 int main(void)
 {	
	 //<alex-20160228> init uart++++
	    NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	    uart_init(115200);	 //串口初始化为115200
	 #ifdef USBDEBUG
	    printf("[athena]usart is ok\r\n");
	 #endif
	 //<alex-20160228> init uart----
	 delay_init(); //delay函数初始化 /*
	 //<alex-20160228>初始化mpu6050I2C+++++
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
	 //<alex-20160228>初始化mpu6050I2C-----
	 
	 LED_Init(); //初始化LED
	 MotorInit();
	 #ifdef MOTOR_TEST
	    MotorPwmFlash(10,10,10,10);
	 #endif
	 #ifdef USBDEBUG
	     printf("Motor init ok!\r\n");
	 #endif
	 
	 /**********************************************
	 主程序入口
	 ***********************************************/
	 while(1)
	 {
		 printf("[athena]start\r\n");
		 printf("mpu6050 %s\r\n",mpu6050_status? "true":"flase");
		 delay_ms(1000);
	 }
	 return 0;
 }

