#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void PWM_TIM3_Set(u16 vol);
void PWM_TIM4_Set(u16 vol);
#endif
