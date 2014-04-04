#include "MyF4Config.h"

/*****************************************/
/*************系统USART1/2配置************/
/*****************************************/
void USART_Config()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;     //定义USART初始化结构体	
	NVIC_InitTypeDef nvicParam;
	/*****************************************/
	/************配置USART1的引脚*************/
	/*****************************************/
	//TX
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;               //选择GPIOB的6脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //设置选中的引脚工作模式，IN：输入模式；OUT：输出模式；AF：复用模式；AN：模拟模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);        //初始化所设置的GPIOD参数
  //RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                //选择GPIOB的7脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //设置选中的引脚工作模式，IN：输入模式；OUT：输出模式；AF：复用模式；AN：模拟模式
                       
  GPIO_Init(GPIOB , &GPIO_InitStructure);
	

/*****************************************/
/**********系统USART端口配置**************/
/*****************************************/

	USART_Cmd(USART3 , DISABLE);          //关闭串口
	//GPIOA的2、3脚复用为USART1的引脚
  GPIO_PinAFConfig(GPIOB , GPIO_PinSource10 , GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOB , GPIO_PinSource11 , GPIO_AF_USART3);
	
	//串口1参数设置
	USART_InitStructure.USART_BaudRate = 115200;                                      //波特率：115200、57600、38400、9600、4800、2400、1200
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                       //表示一个帧中发送或者接收到的数据位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;                            //停止位
  USART_InitStructure.USART_Parity = USART_Parity_No ;                               //奇偶模式
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //使能或关闭硬件流控制模式
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   //使能或关闭发送和接收模式   

	USART_Init(USART3 , &USART_InitStructure);
	//使能USART1
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
  nvicParam.NVIC_IRQChannel = USART3_IRQn;
  nvicParam.NVIC_IRQChannelPreemptionPriority = 8;
  nvicParam.NVIC_IRQChannelSubPriority = 8;
  nvicParam.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicParam);
		
		
	
	USART_Cmd(USART3, ENABLE);
	
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART2_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * 函数名：USART2_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口2，即USART2
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART2_printf( USART2, "\r\n this is a demo \r\n" );
 *            		 USART2_printf( USART2, "\r\n %d \r\n", i );
 *            		 USART2_printf( USART2, "\r\n %s \r\n", j );
 */
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;

        case 'd':										//十进制
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
