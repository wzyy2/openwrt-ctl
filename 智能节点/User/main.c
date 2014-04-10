#include "MyF4Config.h"
#include "bsp.h"
#include "application.h"

//我注释了fputc 要是想用printf发送 自己取消掉 

int main(void)
{
	board_init(); //MCU寄存器的初始化
	device_init(); //设备
	application_init(); //程序初始化
	while(1)
	{		 
		loop_work();
	}  	
}

