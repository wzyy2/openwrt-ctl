//
// ´®¿Ú×´Ì¬»ú
//
#include"uart_state.h"

#define MAX_LEN 50

#ifndef __USART1_STATE
u8 usart1_buffer[MAX_LEN];
#endif
#ifndef __USART2_STATE
u8 usart2_buffer[MAX_LEN];
#endif
#ifndef __USART3_STATE
u8 usart3_buffer[MAX_LEN];
#endif

struct
{
	u8* head[3];
	u8 front[3];
	u8 rear[3];
}uart_queue;

u8 UartState_init()
{
	u8 i;
	for(i=0;i<3;i++){
		uart_queue.head[i]=NULL;
		uart_queue.front[i]=0;
		uart_queue.rear[i]=0;
	}
//#ifndef __USART1_STATE
//	uart_queue.head[0] = &usart1_buffer[0];
//#endif
//#ifndef __USART2_STATE
//	uart_queue.head[1] = &usart2_buffer[0];
//#endif
//#ifndef __USART3_STATE
	uart_queue.head[2] = &usart3_buffer[0];
//#endif

	return 0;
}

u8 Uart_RxBufLen(u8 port)
{
	switch(port)
	{
		case 1:
			return uart_queue.rear[0] - uart_queue.front[0];
		case 2:
			return uart_queue.rear[1] - uart_queue.front[1];
		case 3:
			return uart_queue.rear[2] - uart_queue.front[2];
		default:
			break;
	}
	return 0;
}

int8_t UartAdd(u8 port,u8 ch)
{
	switch(port)
	{
		case 1:
			if(uart_queue.head[0]){
				if(uart_queue.rear[0] > 49)
					return -1;
				*(uart_queue.head[0] + uart_queue.rear[0]) = ch;
				uart_queue.rear[0]++;
			}
			break;
		case 2:
			if(uart_queue.head[1]){
				if(uart_queue.rear[1] > 49)
					return -1;
				*(uart_queue.head[1] + uart_queue.rear[1]) = ch;
				uart_queue.rear[1]++;
			}
			break;
		case 3:
			if(uart_queue.head[2]){
				if(uart_queue.rear[2] > 49)
					return -1;
				*(uart_queue.head[2] + uart_queue.rear[2]) = ch;
				uart_queue.rear[2]++;
			}
			break;
		default:
			break;
	}
	return 0;
}

u8 UartRead(u8 port,u8* ch)
{
	switch(port)
	{
		case 1:
			if(uart_queue.head[0]){
					*ch = *(uart_queue.head[0] + uart_queue.front[0]);
					uart_queue.front[0]++;
					if(uart_queue.front[0] >= uart_queue.rear[0]){
						uart_queue.front[0]=0;uart_queue.rear[0]=0;
					}					
			}
			break;
		case 2:
			if(uart_queue.head[1]){
					*ch = *(uart_queue.head[1] + uart_queue.front[1]);
					uart_queue.front[1]++;
					if(uart_queue.front[1] >= uart_queue.rear[1]){
						uart_queue.front[1]=0;uart_queue.rear[1]=0;
					}		
			}
			break;
		case 3:
			if(uart_queue.head[2]){
					*ch = *(uart_queue.head[2] + uart_queue.front[2]);
					uart_queue.front[2]++;
					if(uart_queue.front[2] >= uart_queue.rear[2]){
						uart_queue.front[2]=0;uart_queue.rear[2]=0;
					}		
			}
			break;
		default:
			break;
	}
	return 0;
}






void UartProcessData(u8 port,u8* data,u8* cmd)
{
  u8  ch;
  static u8 state=SOP_STATE; 
	static u8 LEN_Token ;

  while (Uart_RxBufLen(port))
  {
    UartRead (port, &ch);
    switch (state)
    {
      case SOP_STATE:
        if (ch == UART_SOF)
          state = LEN_STATE;
				printf("1");
        break;
				
      case LEN_STATE:
        LEN_Token = ch;
        state = CMD_STATE;
							printf("2");
        break;
			
      case CMD_STATE:
        *cmd = ch;
        if (LEN_Token)
        {
          state = SOP_STATE;
        }
        else
        {
          state = SOP_STATE;
        }
								printf("3");
        break;

      case DATA_STATE:
				state = SOP_STATE;
        break;
			
      case FCS_STATE:
        state = SOP_STATE;
        break;
			
      default:
       break;
    }
  }
}


