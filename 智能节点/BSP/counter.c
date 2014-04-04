#include "counter.h"

void TIM_Mode_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
            
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);  

	TIM_DeInit(TIM4);
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;            //设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
   /*初始化TIM2定时器 */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
        //编码配置                        编码模式
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM3, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  //TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //使能中断
  //Reset counter
  TIM4->CNT =20000;            
  TIM_Cmd(TIM4, ENABLE);   //使能定时器3
	TIM_DeInit(TIM1);
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;            //设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
   /*初始化TIM2定时器 */
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
        //编码配置                        编码模式
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, 
  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  //TIM_ARRPreloadConfig(TIM3, ENABLE);
  // Clear all pending interrupts
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);   //使能中断
  //Reset counter
  TIM1->CNT =20000;            
  TIM_Cmd(TIM1, ENABLE);   //使能定时器3

}



void TIM3_Mode_Config(void)  //测速
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	EXTI_InitTypeDef 	EXTI_InitStructure;
	//1mhz  1khz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 168;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);   //????????????????
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //????,????????????
	TIM_Cmd(TIM3,ENABLE);    //?????
		

	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;    //????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //?????0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //?????1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //????
	NVIC_Init(&NVIC_InitStructure);     
}




