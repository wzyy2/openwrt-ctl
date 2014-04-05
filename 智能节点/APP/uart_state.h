#ifndef __UART_STATE_H
#define	__UART_STATE_H

#include "MyF4Config.h"




#define SOP_STATE 0
#define LEN_STATE 1
#define CMD_STATE 2
#define DATA_STATE 3
#define FCS_STATE 4

#define UART_SOF 0xfe


u8 UartState_init(void);
u8 Uart_RxBufLen(u8 port);
int8_t UartAdd(u8 port, u8 ch);
u8 UartRead(u8 port, u8* ch);
void UartProcessData(u8 port,u8* data,u8* cmd);


#endif


