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
	
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

sbit OLED_SCL=P3^2;//SCL
sbit OLED_SDA=P3^3;//SDA
sbit OLED_RES =P1^2;//RES

//-----------------OLED�˿ڶ���----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1



//OLED�����ú���
// void OLED_ColorTurn(u8 i);       //OLED��ɫ���Կ��ƣ�i=0������ʾ��i=1��ɫ��ʾ
// void OLED_DisplayTurn(u8 i);     //OLED��ʾ������ƣ�i=0��������i=1��ת180��
// void OLED_WR_Byte(u8 dat,u8 cmd); //��OLEDд��һ���ֽڣ�cmd=0д���cmd=1д����
// void OLED_Set_Pos(u8 x, u8 y);   //����OLED��ʾλ�����꣬x(0-127), y(0-7)
// void OLED_Display_On(void);      //����OLED��ʾ
// void OLED_Display_Off(void);     //�ر�OLED��ʾ
void OLED_Clear(void);           //���OLED��ʾ����
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey); //��ָ��λ����ʾ�ַ���sizey=�����С
// u32 oled_pow(u8 m,u8 n);         //����m��n�η�������������ʾ
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey); //��ʾ���֣�len=����λ��
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey); //��ʾ�ַ���
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey); //��ʾ���֣�no=����������
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]); //��ʾλͼ
void OLED_Init();                //OLED��ʼ������
#endif
	 



