#include "bsp.h"



void GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_StructInit(&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            //设置GPIO的输出方式PP推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 ;	// 推挽 	  
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化指定IO
	
				GPIO_SetBits(GPIOA, GPIO_Pin_8);
				GPIO_SetBits(GPIOA, GPIO_Pin_9);
				GPIO_SetBits(GPIOA, GPIO_Pin_10);
}



void EXTI_Config(void)
{
}



u32 board_init()
{
  RCC_Config();       //系统时钟配置	 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	delay_init();
	USART_Config(); 	
  GPIO_Config();
//EXTI_Config();
	return 0;
}


