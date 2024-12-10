#ifndef __MYIIC_H
#define __MYIIC_H 

#include "main.h" 	
#include "delay.h"

//#define soft_iic
#define		EE_IIC
#define I2C_PORT                GPIOB

#define I2C_SCL_PIN 			GPIO_PIN_6
#define I2C_SCL_PORT 		    GPIOB

#define I2C_SDA_PIN 			GPIO_PIN_7
#define I2C_SDA_PORT 		    GPIOB

#define I2C_SCL_H			 	(I2C_SCL_PORT->BSRR = I2C_SCL_PIN)
#define I2C_SCL_L	            (I2C_SCL_PORT->BRR = I2C_SCL_PIN)

#define I2C_SDA_H				(I2C_SDA_PORT->BSRR = I2C_SDA_PIN)
#define I2C_SDA_L				(I2C_SDA_PORT->BRR = I2C_SDA_PIN)

#define READ_I2C_SDA   			((I2C_SDA_PORT->IDR & I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */

#define EE_SDA_HIGH()		    I2C_SDA_H
#define	EE_SDA_LOW()		    I2C_SDA_L
#define	EE_SCL_HIGH()		    I2C_SCL_H
#define	EE_SCL_LOW()		    I2C_SCL_L
#define	EE_SDA_READ()		    READ_I2C_SDA

//I2C���в�������
void I2C_Init(void);                //��ʼ��I2C��IO��				 
void I2C_Start(void);				//����I2C��ʼ�ź�
void I2C_Stop(void);	  			//����I2Cֹͣ�ź�
void I2C_Send_Byte(u8 txd);			//I2C����һ���ֽ�
u8 I2C_Read_Byte(void);//I2C��ȡһ���ֽ�
u8 I2C_Wait_Ack(void); 				//I2C�ȴ�ACK�ź�
void I2C_Ack(void);					//I2C����ACK�ź�
void I2C_NAck(void);				//I2C������ACK�ź�

void I2C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 I2C_Read_One_Byte(u8 daddr,u8 addr);	 

void EE_delay(void);



#endif
















