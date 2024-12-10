#include "24cxx.h" 
#include "delay.h" 	


#define    SOFT_VERSION    (0x01)


void bsp_InitParam(void)
{
	u8 i = 20;
	u8 result = 0;
	
    uint8_t temp_group=1;
    uint8_t temp_dev=1;
    
	while(i--)
	{
		AT24CXX_Read(FLAG_ADDR,&result,1);
		if(result == SOFT_VERSION)
		{
			break;
		}
		else
        {
			delay_ms(10);
        }
	}
	if(result != SOFT_VERSION)
	{
        AT24CXX_WriteOneByte(FLAG_ADDR,SOFT_VERSION);
		AT24CXX_Write(GROUP_SN_ADDR,&temp_group,1);
        AT24CXX_Write(GROUP_DEV_ADDR,&temp_dev,1);
	}
	delay_ms(50);
	
    AT24CXX_Read(GROUP_SN_ADDR,&groupSN,1);
    AT24CXX_Read(GROUP_DEV_ADDR,&devSN,1);
    
    
}

//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	//GPIOB8,B9��ʼ������
	GPIO_InitTypeDef GPIO_InitStruct = {0};	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = IIC_SCL_PIN|IIC_SDA_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(IIC_PORT, &GPIO_InitStruct);
  
	IIC_SCL_H;
	IIC_SDA_H;
	
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0; 
	IIC_SDA_H;delay_us(1);	   
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;    	    
    IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
//        IIC_SDA=(txd&0x80)>>7;
		if(((txd&0x80)))	
		{
				IIC_SDA_H;
		}else{   
			IIC_SDA_L;
		}
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	for(i=0;i<8;i++ )
	{
		IIC_SCL_L; 
		delay_us(2);
		IIC_SCL_H;
		receive<<=1;
		if(READ_SDA)receive++;   
		delay_us(1); 	
	}					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0);	    //����д����
	IIC_Wait_Ack();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();
	}
    IIC_Send_Byte(ReadAddr&0xff);   //���͵͵�ַ
	IIC_Wait_Ack(); 	     
	IIC_Start();  	 	   
	IIC_Send_Byte((0XA0)|0x01); //�������ģʽ			
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start(); 
	IIC_Send_Byte(0XA0);	    //����д����
	IIC_Wait_Ack();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();
	}
    IIC_Send_Byte(WriteAddr&0xff);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}													    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(0x0000);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X01)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(0x0000,0X01);
	    temp=AT24CXX_ReadOneByte(0x0000);	 
		
//		AT24CXX_Write(10,Init_eeprom,100);
		
		if(temp==0X01)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}








