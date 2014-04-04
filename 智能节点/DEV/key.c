#include "key.h"



void KEY_Configuration(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 EXTI_InitTypeDef 	EXTI_InitStructure;
	

	/* Configure the NVIC Preemption Priority Bits */  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOE, &GPIO_InitStructure);               
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2   );
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);
}

void delay()
{ 
	u32 a;
	a=600000;
	while(a--);
}

/*void EXTI2_IRQHandler(void)
{
 if( EXTI_GetITStatus(EXTI_Line2))
  {    
    EXTI_ClearFlag(EXTI_Line2);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0)
		{
			delay();
		}
  }  
}*/

/*void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line7))
  { 
		
    EXTI_ClearFlag(EXTI_Line7);
		vsync=0;
    EXTI_ClearITPendingBit(EXTI_Line7);
  }   
	if(EXTI_GetITStatus(EXTI_Line6))
  { 
		
    EXTI_ClearFlag(EXTI_Line6);

    EXTI_ClearITPendingBit(EXTI_Line6);
  }  
}

//40*40

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4))
  { 
		
    EXTI_ClearFlag(EXTI_Line4);
		vsync++;
		row=0;		
    EXTI_ClearITPendingBit(EXTI_Line4);
  }  
}

*/

