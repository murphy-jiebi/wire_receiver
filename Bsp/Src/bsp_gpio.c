#include "bsp_gpio.h"


void bsp_InitGpio(void)
{
    //GPIOB8,B9初始化设置
	GPIO_InitTypeDef GPIO_InitStruct = {0};	
	__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
 /********************************输出********************************************************/   
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  
    GPIO_InitStruct.Pin = LED_PIN;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CTL_485_PIN;
	HAL_GPIO_Init(CTL_485_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH_PWR_PIN;
	HAL_GPIO_Init(CH_PWR_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH1_CTL_PIN;
	HAL_GPIO_Init(CH1_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH2_CTL_PIN;
	HAL_GPIO_Init(CH2_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH3_CTL_PIN;
	HAL_GPIO_Init(CH3_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH4_CTL_PIN;
	HAL_GPIO_Init(CH4_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH5_CTL_PIN;
	HAL_GPIO_Init(CH5_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH6_CTL_PIN;
	HAL_GPIO_Init(CH6_CTL_PORT, &GPIO_InitStruct);
    

    
/********************************输入********************************************************/
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    
    GPIO_InitStruct.Pin = PWR_INT_PIN;
	HAL_GPIO_Init(PWR_INT_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH1_DET_PIN;
	HAL_GPIO_Init(CH1_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH2_DET_PIN;
	HAL_GPIO_Init(CH2_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH3_DET_PIN;
	HAL_GPIO_Init(CH3_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH4_DET_PIN;
	HAL_GPIO_Init(CH4_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH5_DET_PIN;
	HAL_GPIO_Init(CH5_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH6_DET_PIN;
	HAL_GPIO_Init(CH6_DET_PORT, &GPIO_InitStruct);
    
    CH1_CTL_DIS;
    CH2_CTL_DIS;
    CH3_CTL_DIS;
    CH4_CTL_DIS;
    CH5_CTL_DIS;
    CH6_CTL_DIS;
    
    CH_PWR_EN;
}

void LedToggle(void)
{
    HAL_GPIO_TogglePin(LED_PORT,LED_PIN);
}
void RS485ModeSet(uint8_t mode)
{
    if(mode)
    {
        CTL_485_H;
    }else{
        CTL_485_L;
    }
}