/****************************************************/
//    在此DEMO中加入USART1/USART2的输出与GPIOE接口的1
//个状态灯的定义,并且打开了FPU，加入了ARM_MATH.H
//数学运算头文件；系统时钟来源为HSE 25MHz，系统主
//频定义为最快速度168MHz.
/****************************************************/
 

#include "MyF4Config.h"

#include "5110.h"  
#include "MotorCtl.h"  
#include "24l01.h" 
#include "lcd.h"
#include "counter.h"  
#include "math.h"

int main(void)
{
//  RCC_Config();       //系统时钟配置	
	delay_init();
	USART_Config(); 
	MotorInit();
	MotorCtl(10000,0);
	NRF24L01_Init();    	//初始化NRF24L01 
	while(NRF24L01_Check())
	{
		USART_printf(USART3, "%d",SPI3->CR1);
	}
	
			LCD_Init();
	//POINT_COLOR=RED;
//r	LCD_DisplayOn();
 // NRF24L01_TX_Mode();	
  //TIM_Mode_Config();
	//
	//LCD5110_init();
	//LCD5110_clear();

	while(1)
	{	
		USART_printf(USART3, "%d",SPI3->CR1);
	}
}
