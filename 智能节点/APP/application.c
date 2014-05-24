#include "application.h" 

#include "MotorCtl.h"   // 电机控制
//#include "24l01.h" 
#include "lcd.h"
#include "key.h"  
#include "counter.h"   //编码器
#include "uart_state.h"
#include "oled.h"

u32 device_init()
{
  LCD_Init();  //初始LCD

	
	return 0;
}
u32 application_init()
{
	device_init();
	UartState_init();  //状态机初始化
	OLED_Init();
	return 0;
}

void loop_work()
{
	u8 cmd=0;
	UartProcessData(3,NULL,&cmd); //状态机读取
	if(cmd)
		LCD_ShowxNum(156,300,cmd,3,16,0);//显示ADC的值
	//OLED_SDA=1;
	OLED_SDA=1;
	OLED_SCL=1;
	OLED_DC=1;
	OLED_RST=1;
	//OLED_Setxy(0,0);
	//OLED_Fill(0xff);
	switch(cmd)
	{
		case 0x01:   //关灯
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
			break;
		case 0x02:   //开灯
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			break;
		case 0x03:   //风扇关
			GPIO_SetBits(GPIOA, GPIO_Pin_9);
			GPIO_SetBits(GPIOA, GPIO_Pin_10);
			break;
		case 0x04:   //风扇一档
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);		
 	  	GPIO_SetBits(GPIOA, GPIO_Pin_10);
			break;
		case 0x05:   //风扇二档
			GPIO_SetBits(GPIOA, GPIO_Pin_9);
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
			break;
		case 0x06:   //状态读取
			break;
	}
#ifdef DEBUG
//printf("%d");
//LCD_ShowxNum(156,300,image[76798],3,16,0);//显示ADC的值		
//visual_scope(1,2,3,4,USART2); // 串口波形显示
#endif 
}

