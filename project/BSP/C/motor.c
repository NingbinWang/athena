#include "motor.h"
u16 MOTO1_PWM = 0;
u16 MOTO2_PWM = 0;
u16 MOTO3_PWM = 0;
u16 MOTO4_PWM = 0;
/************************************************
motor init
PA0 PA1 PA2 PA3
**************************************************/
void MotorInit(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	u16 PrescalerValue = 0;    
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
	PrescalerValue = (u16) (SystemCoreClock / 24000000) - 1;
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = 999; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =PrescalerValue; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM2 Channel2 PWM模式	 
	//TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_Pulse = 0;    //0
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC2
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}
/***********************************************
:MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)

***********************************************/
void MotorPwmFlash(u16 MOTO1_PWM,u16 MOTO2_PWM,u16 MOTO3_PWM,u16 MOTO4_PWM)
{		
     if(MOTO1_PWM>=Motor_PwmMax)	MOTO1_PWM = Motor_PwmMax;
     if(MOTO2_PWM>=Motor_PwmMax)	MOTO2_PWM = Motor_PwmMax;
     if(MOTO3_PWM>=Motor_PwmMax)	MOTO3_PWM = Motor_PwmMax;
     if(MOTO4_PWM>=Motor_PwmMax)	MOTO4_PWM = Motor_PwmMax;
     if(MOTO1_PWM<=0)	MOTO1_PWM = 0;
     if(MOTO2_PWM<=0)	MOTO2_PWM = 0;
     if(MOTO3_PWM<=0)	MOTO3_PWM = 0;
     if(MOTO4_PWM<=0)	MOTO4_PWM = 0;
	    TIM_SetCompare1(TIM2,MOTO1_PWM);
	    TIM_SetCompare2(TIM2,MOTO2_PWM);
	    TIM_SetCompare3(TIM2,MOTO3_PWM);
	    TIM_SetCompare4(TIM2,MOTO4_PWM);
}