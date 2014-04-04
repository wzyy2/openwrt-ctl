#ifndef __5110_H
#define	__5110_H


#include "MyF4Config.h"

#define ADC1_DR_Address    ((u32)0x4001244C)

#define sce0   GPIO_ResetBits(GPIOE, GPIO_Pin_10)  //片选
#define res0   GPIO_ResetBits(GPIOE, GPIO_Pin_11)  //复位,0复位
#define dc0    GPIO_ResetBits(GPIOE, GPIO_Pin_12)   //1写数据，0写指令
#define sdin0  GPIO_ResetBits(GPIOE, GPIO_Pin_13)   //数据
#define sclk0  GPIO_ResetBits(GPIOE, GPIO_Pin_14)   //时钟

#define sce1   GPIO_SetBits(GPIOE, GPIO_Pin_10)  //片选
#define res1   GPIO_SetBits(GPIOE, GPIO_Pin_11)  //复位,0复位
#define dc1    GPIO_SetBits(GPIOE, GPIO_Pin_12)   //1写数据，0写指令
#define sdin1  GPIO_SetBits(GPIOE, GPIO_Pin_13)   //数据
#define sclk1  GPIO_SetBits(GPIOE, GPIO_Pin_14)   //时钟

void LCD5110_write_byte(unsigned char dt, unsigned char command);
void LCD5110_init(void);
void LCD5110_set_XY(unsigned char X, unsigned char Y);
void LCD5110_clear(void);
void LCD5110_write_char(unsigned char c);
void LCD5110_write_String(unsigned char X,unsigned char Y,char *s);
void LCD5110_write_shu(unsigned char row, unsigned char page,unsigned char c);
void LCD5110_write_shuzi(unsigned char X,unsigned char Y,char s);
void LCD5110_write_hanzi(unsigned char row, unsigned char page,unsigned char c);


#endif