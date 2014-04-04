#ifndef _MYF4CONFIG_H_
#define _MYF4CONFIG_H_

#include "stm32f4xx.h"
//#include "arm_math.h"
#include "misc.h"
#include <stdarg.h>
#include "stdio.h"

//  ???????
#define my_abs(x)  ((x<0)?(0-(x)):(x))     // ????????
#define my_Nabs(x) ((x<0)?(x):(0-(x)))     // ???????????
//  ??????
#define Max(a,b)   (((a)<(b))?(b):(a))     // ????
#define Min(a,b)   (((a)>(b))?(b):(a))     // ????


/************************************************/
/******************系统接口定义******************/
/************************************************/
//状态灯接口定义
#define LED            GPIOE          //LED灯所在的GPIO端口
#define Red            GPIO_Pin_1     //LED灯所在的引脚
//USART1接口定义
#define COM_PORT1      USART3         //系统的USART1定义为COM1
#define GPIO_USART1    GPIOD          //系统USART1所在的GPIO端口
#define COM1_TX        GPIO_Pin_8      //系统USART1的发送引脚
#define COM1_RX        GPIO_Pin_9      //系统USART1的接收引脚
//USART2接口定义
#define COM_PORT2      USART2         //系统的USART2定义为COM2
#define GPIO_USART2    GPIOD          //系统USART2所在的GPIO端口
#define COM2_TX        GPIO_Pin_5     //系统USART2的发送引脚
#define COM2_RX        GPIO_Pin_6     //系统USART2的接收引脚

#define    BITBAND(addr, bitnum)    ((addr &0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr)) 

#define BIT_ADDR(addr,bitnum)  MEM_ADDR(BITBAND(addr,bitnum)) 
#define GPIOA_ODR_Addr        (GPIOA_BASE+20)       //0x40020014 
#define GPIOB_ODR_Addr        (GPIOB_BASE+20)       //0x40020414 
#define GPIOC_ODR_Addr        (GPIOC_BASE+20)       //0x40020814 
#define GPIOD_ODR_Addr        (GPIOD_BASE+20)       //0x40020C14 
#define GPIOE_ODR_Addr        (GPIOE_BASE+20)       //0x40021014 
#define GPIOF_ODR_Addr        (GPIOF_BASE+20)       //0x40021414 
#define GPIOG_ODR_Addr        (GPIOG_BASE+20)       //0x40021814 
#define GPIOH_ODR_Addr        (GPIOH_BASE+20)       //0x40021C14 
#define GPIOI_ODR_Addr        (GPIOI_BASE+20)        //0x40022014 
#define GPIOA_IDR_Addr        (GPIOA_BASE+16)       //0x40020010 
#define GPIOB_IDR_Addr        (GPIOB_BASE+16)       //0x40020410 
#define GPIOC_IDR_Addr        (GPIOC_BASE+16)       //0x40020810 
#define GPIOD_IDR_Addr        (GPIOD_BASE+16)       //0x40020C10 
#define GPIOE_IDR_Addr        (GPIOE_BASE+16)        //0x40021010 
#define GPIOF_IDR_Addr        (GPIOF_BASE+16)        //0x40021410 
#define GPIOG_IDR_Addr        (GPIOG_BASE+16)       //0x40021810 
#define GPIOH_IDR_Addr       (GPIOF_BASE+16)     //0x40021C10 
#define GPIOI_IDR_Addr       (GPIOG_BASE+16)      //0x40022010 
#define PAout(n)  BIT_ADDR(GPIOA_ODR_Addr,n)          //GPIOA????? 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)         //GPIOA????? 
#define PBout(n)  BIT_ADDR(GPIOB_ODR_Addr,n)         //GPIOB????? 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)         //GPIOB????? 
#define PCout(n)  BIT_ADDR(GPIOC_ODR_Addr,n)         //GPIOC????? 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)         //GPIOC????? 
#define PDout(n)  BIT_ADDR(GPIOD_ODR_Addr,n)          //GPIOD????? 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)         //GPIOD????? 
#define PEout(n)  BIT_ADDR(GPIOE_ODR_Addr,n)         //GPIOE????? 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)        //GPIOE????? 


/******************系统配置函数声明**************/
void RCC_Config(void);       //系统时钟配置
void USART_Config(void);     //USART端口配置

/******************功能函数声明******************/
int fputc(int ch , FILE *f);
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void delay_init(void);
void delay_ms(__IO uint32_t nTime);
void delay_us(__IO uint32_t nTime);
void TimingDelay_Decrement(void);




#endif 
