#ifndef __24CXX_H
#define __24CXX_H
  
#include "main.h"

#define IIC_PORT					GPIOB
#define IIC_SCL_PIN  				GPIO_PIN_8
#define IIC_SDA_PIN  				GPIO_PIN_9


#define E2ROM_START_ADDR    		0x0010
#define E2ROM_DATA_SIZE     		sizeof(struct e2rom_data)

#define e2rom_addr(mb)      		(E2ROM_START_ADDR + (uint32_t)(&(((struct e2rom_data *)0)->mb)))
#define e2rom_len(mb)       		((uint8_t)(sizeof(((struct e2rom_data *)0)->mb)))


#define IIC_SCL_H			 		HAL_GPIO_WritePin(IIC_PORT, IIC_SCL_PIN, GPIO_PIN_SET)
#define IIC_SCL_L					HAL_GPIO_WritePin(IIC_PORT, IIC_SCL_PIN, GPIO_PIN_RESET)

#define IIC_SDA_H					HAL_GPIO_WritePin(IIC_PORT, IIC_SDA_PIN, GPIO_PIN_SET)
#define IIC_SDA_L					HAL_GPIO_WritePin(IIC_PORT, IIC_SDA_PIN, GPIO_PIN_RESET)	

#define READ_SDA   					((IIC_PORT->IDR & IIC_SDA_PIN) != 0)	/* 读SDA口线状态 */

#define AT24C01						127
#define AT24C02						255
#define AT24C04						511
#define AT24C08						1023
#define AT24C16						2047
#define AT24C32						4095
#define AT24C64	  					8191
#define AT24C128					16383
#define AT24C256					32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE 					AT24C256
			
#define FLAG_ADDR                   (1)            
#define GROUP_SN_ADDR               (10)
#define GROUP_DEV_ADDR              (15)


uint8_t  AT24CXX_ReadOneByte(uint16_t ReadAddr);									//指定地址读取一个字节
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);					//指定地址写入一个字节
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);		//指定地址开始写入指定长度的数据
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);						//指定地址开始读取指定长度数据
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);		//从指定地址开始写入指定长度的数据
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   		//从指定地址开始读出指定长度的数据

uint8_t AT24CXX_Check(void);  														//检查器件
void AT24CXX_Init(void); 															//初始化IIC
			
void bsp_InitParam(void);
	
void IIC_Start(void);																//发送IIC开始信号
void IIC_Stop(void);	  															//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);													//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);											//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 														//IIC等待ACK信号
void IIC_Ack(void);																	//IIC发送ACK信号
void IIC_NAck(void);																//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  



#endif














