#include "MyF4Config.h"


/*********串口输出重定向**********/
int fputc(int ch , FILE *f)
{
	//USART_SendData(COM_PORT1 , (uint8_t)ch);
	//while( USART_GetFlagStatus (COM_PORT1 , USART_FLAG_TC ) == RESET);
	return ch;
}



static __IO uint32_t TimingDelay;


void delay_init()	 
{

  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1);
  }

}			

void delay_us(__IO uint32_t nTime)
{	 		  	  
	TimingDelay = nTime;   
	while(TimingDelay != 0);     
}


void delay_ms(__IO uint32_t nTime)
{	 		  	  
	TimingDelay = nTime*1000;   
	while(TimingDelay != 0);     
}



void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
   
