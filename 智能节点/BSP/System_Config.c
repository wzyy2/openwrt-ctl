/**********************************************/
/****************系统内部配置******************/
/**********************************************/
#include "MyF4Config.h"


/**********************************************/
/****************系统时钟配置******************/
/**********************************************/
//系统时钟配置在最高速度168MHz
void RCC_Config()
{
	RCC_DeInit();                                  //RCC寄存器初始化
  RCC_HSEConfig(RCC_HSE_ON);                     //使用外部时钟
  if ( RCC_WaitForHSEStartUp() == SUCCESS )      //等待外部时钟启动  25MHz
  {
		RCC_PLLCmd(DISABLE);                         //配置PLL前应先关闭主PLL
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);   //选择PLL时钟为系统时钟  168MHz
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7); //PLL时钟配置，公式详见‘system_stm43f4xx.c’ Line149
    RCC_HCLKConfig(RCC_SYSCLK_Div1);             //HCLK(AHB)时钟为系统时钟1分频 168MHz
    RCC_PCLK1Config(RCC_HCLK_Div1);              //PCLK1(APB1)时钟为HCLK时钟4分频 42MHz;TIM2,3,4,5,6,7,12,13,14为84MHz
    RCC_PCLK2Config(RCC_HCLK_Div1);              //PCLK2(APB2)时钟为HCLK时钟2分频 84Mhz;TIM1,8,9,10,11为168MHz
  	//FLASH_SetLatency(FLASH_Latency_5);           //设置FLASH延时周期数为5
		//FLASH_PrefetchBufferCmd(ENABLE);             //使能FLASH预取缓存
   RCC_PLLCmd(ENABLE);                          //PLL时钟开启
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) { } //等待PLL时钟准备好
		while(RCC_GetSYSCLKSource() != 0x08) { }
  }
	//使能GPIOA、GPIOB、GPIOC、GPIOD、GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
	                              RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
	//使能USART1,2、使能TIM2,3,5,6,9使能SPI1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4|RCC_APB1Periph_SPI3 , ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
}




