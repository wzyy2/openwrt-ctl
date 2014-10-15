#ifndef __OLED_H
#define __OLED_H			  	 
#include "MyF4Config.h"
  

  
#define OLED_DC_PIN    15  
#define OLED_SDA_PIN   7  
#define OLED_SCL_PIN   14  
#define OLED_RST_PIN   11  
#define OLED_DC     PBout(OLED_DC_PIN)  
#define OLED_SDA    PBout(OLED_SDA_PIN)  
#define OLED_SCL    PBout(OLED_SCL_PIN)  
#define OLED_RST    PDout(OLED_RST_PIN)  
 
#define XLevelL     0x00  
#define XLevelH     0x10  
#define XLevel      ((XLevelH&0x0F)*16+XLevelL)  
#define Max_Column  128  
#define Max_Row     64  
#define Brightness  0xCF   
#define X_WIDTH 128  
#define Y_WIDTH 64  
//本构件实现的接口函数  
void OLED_WRCMD(u8 com);  
void OLED_WRDATA(u8 dat);  
void OLED_Setxy(u8 x, u8 y);    //OLED 设置坐标  
void OLED_Fill(u8 bmp_dat);   //bmp_dat=0x00全屏灭，bmp_dat=0xff全屏亮  
void OLED_Init(void); //OLED初始化    
void OLED_6x8(u8 x,u8 y,u8 ch[]);//显示6*8一组标准ASCII字符串    显示的坐标（x,y），y为页范围0～7  
void OLED_Cler_6x8(u8 x,u8 y,u8 n);//清除N个6*8字符  
void OLED_8x16(u8 x,u8 y,u8 ch[]);//显示8*16一组标准ASCII字符串   显示的坐标（x,y），y为页范围0～7  
void OLED_Cler_8x16(u8 x,u8 y,u8 n); //清除n个8*16字符  
void OLED_16x16(u8 x,u8 y,u8 N);//显示16*16点阵  显示的坐标（x,y），y为页范围0～7  
void OLED_Cler_16x16(u8 x,u8 y,u8 n);//清除n个16*16字  
void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);//显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*  
void OLED_Refresh_Gram(void);  
void OLED_DRAWPoint(u8 x,u8 y,u8 t);  
#endif  


