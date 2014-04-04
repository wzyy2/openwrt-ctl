#include "MyF4Config.h"

//Data send adapt CRC16 verification,The following is the function of CRC16,please refer
 //-------------------------------------------------------------------------------------------
 unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
 {
     unsigned short CRC_Temp;
     unsigned char i,j;
     CRC_Temp = 0xffff;
 
    for (i=0;i<CRC_CNT; i++){      
         CRC_Temp ^= Buf[i];
         for (j=0;j<8;j++) {
             if (CRC_Temp & 0x01)
                 CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
             else
                 CRC_Temp = CRC_Temp >> 1;
         }
     }
     return(CRC_Temp);
 }
 //-------------------------------------------------------------------------------------------
 /*The data from computer to MPU is like this:
 Ch1_Addr_LL,Ch1_Addr_LH,
 Ch1_Addr_HL,Ch1_Addr_HH,
 Ch2_Addr_LL,Ch2_Addr_LH,
 Ch2_Addr_HL,Ch2_Addr_HH,
 Ch3_Addr_LL,Ch3_Addr_LH,
 Ch3_Addr_HL,Ch3_Addr_HH,
 Ch4_Addr_LL,Ch4_Addr_LH,
 Ch4_Addr_HL,Ch4_Addr_HH,
 CRC16_L,CRC16_H
 
//-------------------------------------------------------------------------------------------
 The data from MPU to computer should be like this:
 Ch1Data_L,Ch1Data_H,
 Ch2Data_L,Ch2Data_H,
 Ch3Data_L,Ch3Data_H,
 Ch4Data_L,Ch4Data_H,
 CRC16_L,CRC16_H
 */
void visual_scope(int16_t ch1,int16_t ch2,int16_t ch3,int16_t ch4)
{

	unsigned char Buf[16];
	uint16_t Crc;
	Buf[0] = ch1 & 0x00ff;Buf[1] = (ch1 & 0xff00)>>8;
	Buf[2] = ch2 & 0x00ff;Buf[3] = (ch2 & 0xff00)>>8;
	Buf[4] = ch3 & 0x00ff;Buf[5] = (ch3 & 0xff00)>>8;
	Buf[6] = ch4 & 0x00ff;Buf[7] = (ch4 & 0xff00)>>8;
	USART_SendData(USART3, Buf[0]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[1]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[2]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[3]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[4]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[5]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[6]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, Buf[7]);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	Crc = CRC_CHECK(Buf, 8);
	USART_SendData(USART3, Crc & 0x00ff);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
	USART_SendData(USART3, (Crc & 0xff00)>>8);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
}

