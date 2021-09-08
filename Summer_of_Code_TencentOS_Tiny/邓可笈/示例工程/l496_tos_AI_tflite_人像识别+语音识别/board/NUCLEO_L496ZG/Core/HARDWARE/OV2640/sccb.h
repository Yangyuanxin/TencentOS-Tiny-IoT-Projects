#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//OVϵ������ͷ SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//IO��������	 
//#define SCCB_SCL    		PBout(14)	 	//SCL
//#define SCCB_SDA    		PBout(7) 		//SDA	 

//#define SCCB_READ_SDA   PDin(7)  		//����SDA 
//IO��������
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=0<<5*2;}	//PD7 ����
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=1<<5*2;} 	//PD7 ���
#define SCCB_ID   			0X60  			//OV2640��ID


//IO��������
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=0<<5*2;}	//PD7 ����
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=1<<5*2;} 	//PD7 ���


//IO��������	 
//#define SCCB_SCL    		PBout(14)	 	//SCL
//#define SCCB_SDA    		PBout(7) 		//SDA	 

//#define SCCB_READ_SDA   PDin(7)  		//����SDA    
#define SCCB_ID   			0X60  			//OV2640��ID


///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);

void SCCB_SCL(u8 sccb_scl);
void SCCB_SDA(u8 sccb_sda);
u8 SCCB_READ_SDA(void);
//#define SCCB_SCL SCCB_SCL_OUT(SCCB_SCL)
#endif













