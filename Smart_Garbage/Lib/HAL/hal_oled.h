#ifndef __OLED_H
#define __OLED_H

#include "Config.h"		
#include "STC8G_H_I2C.h"  
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_NVIC.h"	 
 
//#define  u8 unsigned char 
//#define  u16 unsigned int
//#define  u32 unsigned int
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

sbit OLED_SCL=P3^2;//SCL
sbit OLED_SDA=P3^3;//SDA
sbit OLED_RES =P1^2;//RES

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1



//OLED控制用函数
// void OLED_ColorTurn(u8 i);       //OLED颜色反显控制，i=0正常显示，i=1反色显示
// void OLED_DisplayTurn(u8 i);     //OLED显示方向控制，i=0正常方向，i=1旋转180度
// void OLED_WR_Byte(u8 dat,u8 cmd); //向OLED写入一个字节，cmd=0写命令，cmd=1写数据
// void OLED_Set_Pos(u8 x, u8 y);   //设置OLED显示位置坐标，x(0-127), y(0-7)
// void OLED_Display_On(void);      //开启OLED显示
// void OLED_Display_Off(void);     //关闭OLED显示
void OLED_Clear(void);           //清空OLED显示内容
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey); //在指定位置显示字符，sizey=字体大小
// u32 oled_pow(u8 m,u8 n);         //计算m的n次方，用于数字显示
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey); //显示数字，len=数字位数
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey); //显示字符串
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey); //显示汉字，no=汉字索引号
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]); //显示位图
void OLED_Init();                //OLED初始化函数
#endif
	 



