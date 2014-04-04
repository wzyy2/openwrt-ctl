#ifndef __VISUAL_STOPE_H
#define __VISUAL_STOPE_H

#include "MyF4Config.h"


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
void visual_scope(int16_t ch1,int16_t ch2,int16_t ch3,int16_t ch4,USART_TypeDef* USARTX);



#endif
