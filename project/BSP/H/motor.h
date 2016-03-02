#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#define Motor_PwmMax 999

void MotorPwmFlash(u16 MOTO1_PWM,u16 MOTO2_PWM,u16 MOTO3_PWM,u16 MOTO4_PWM);
void MotorInit(void);

#endif
