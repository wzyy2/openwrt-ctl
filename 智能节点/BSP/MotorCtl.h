#ifndef __MOTORCTL_H
#define __MOTORCTL_H	 	

#include "MyF4Config.h"



void TIM2_PWM_Init(u16 arr,u16 psc);
void PWMInit(void);
void TIM3_PWM_Init(void);
void MotorInit(void);
void MotorRCtl(int16_t speed,unsigned char direction);
void MotorLCtl(int16_t speed,unsigned char direction);
void STOP(void);
void MotorCtl( int16_t speed,int16_t PIDCtlOut);

#endif
