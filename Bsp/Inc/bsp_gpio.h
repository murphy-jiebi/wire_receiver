#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "main.h" 	


#define LED_PIN             GPIO_PIN_4
#define LED_PORT            GPIOA

#define PWR_INT_PORT        GPIOA
#define PWR_INT_PIN         GPIO_PIN_0

#define CTL_485_PORT        GPIOA
#define CTL_485_PIN         GPIO_PIN_1

#define CH_PWR_PORT         GPIOB
#define CH_PWR_PIN          GPIO_PIN_5

#define CH1_CTL_PORT        GPIOB
#define CH1_CTL_PIN         GPIO_PIN_11

#define CH2_CTL_PORT        GPIOB
#define CH2_CTL_PIN         GPIO_PIN_1

#define CH3_CTL_PORT        GPIOB
#define CH3_CTL_PIN         GPIO_PIN_0

#define CH4_CTL_PORT        GPIOA
#define CH4_CTL_PIN         GPIO_PIN_7

#define CH5_CTL_PORT        GPIOA
#define CH5_CTL_PIN         GPIO_PIN_6

#define CH6_CTL_PORT        GPIOA
#define CH6_CTL_PIN         GPIO_PIN_5

#define CH6_DET_PORT        GPIOA
#define CH6_DET_PIN         GPIO_PIN_8

#define CH5_DET_PORT        GPIOB
#define CH5_DET_PIN         GPIO_PIN_15

#define CH4_DET_PORT        GPIOB
#define CH4_DET_PIN         GPIO_PIN_14

#define CH3_DET_PORT        GPIOB
#define CH3_DET_PIN         GPIO_PIN_13

#define CH2_DET_PORT        GPIOB
#define CH2_DET_PIN         GPIO_PIN_12

#define CH1_DET_PORT        GPIOB
#define CH1_DET_PIN         GPIO_PIN_10


#define READ_PWR_INT        ((PWR_INT_PORT->IDR & PWR_INT_PIN) != 0)
#define READ_CHG_INT        ((CHG_INT_PORT->IDR & CHG_INT_PIN) != 0)
#define READ_CH1_DET        ((CH1_DET_PORT->IDR & CH1_DET_PIN) != 0)
#define READ_CH2_DET        ((CH2_DET_PORT->IDR & CH2_DET_PIN) != 0)
#define READ_CH3_DET        ((CH3_DET_PORT->IDR & CH3_DET_PIN) != 0)
#define READ_CH4_DET        ((CH4_DET_PORT->IDR & CH4_DET_PIN) != 0)
#define READ_CH5_DET        ((CH5_DET_PORT->IDR & CH5_DET_PIN) != 0)
#define READ_CH6_DET        ((CH6_DET_PORT->IDR & CH6_DET_PIN) != 0)

#define READ_CH1_CTL        ((CH1_CTL_PORT->ODR & CH1_CTL_PIN) != 0)
#define READ_CH2_CTL        ((CH2_CTL_PORT->ODR & CH2_CTL_PIN) != 0)
#define READ_CH3_CTL        ((CH3_CTL_PORT->ODR & CH3_CTL_PIN) != 0)
#define READ_CH4_CTL        ((CH4_CTL_PORT->ODR & CH4_CTL_PIN) != 0)
#define READ_CH5_CTL        ((CH5_CTL_PORT->ODR & CH5_CTL_PIN) != 0)
#define READ_CH6_CTL        ((CH6_CTL_PORT->ODR & CH6_CTL_PIN) != 0)


#define LED_ON              (LED_PORT->BSRR = LED_PIN)
#define LED_OFF             (LED_PORT->BRR = LED_PIN)

#define CTL_485_H           (CTL_485_PORT->BSRR = CTL_485_PIN)
#define CTL_485_L           (CTL_485_PORT->BRR = CTL_485_PIN)

#define CH_PWR_EN           (CH_PWR_PORT->BSRR = CH_PWR_PIN)
#define CH_PWR_DIS          (CH_PWR_PORT->BRR = CH_PWR_PIN)

#define CH1_CTL_EN          (CH1_CTL_PORT->BSRR = CH1_CTL_PIN)
#define CH1_CTL_DIS         (CH1_CTL_PORT->BRR = CH1_CTL_PIN)

#define CH2_CTL_EN          (CH2_CTL_PORT->BSRR = CH2_CTL_PIN)
#define CH2_CTL_DIS         (CH2_CTL_PORT->BRR = CH2_CTL_PIN)

#define CH3_CTL_EN          (CH3_CTL_PORT->BSRR = CH3_CTL_PIN)
#define CH3_CTL_DIS         (CH3_CTL_PORT->BRR = CH3_CTL_PIN)

#define CH4_CTL_EN          (CH4_CTL_PORT->BSRR = CH4_CTL_PIN)
#define CH4_CTL_DIS         (CH4_CTL_PORT->BRR = CH4_CTL_PIN)

#define CH5_CTL_EN          (CH5_CTL_PORT->BSRR = CH5_CTL_PIN)
#define CH5_CTL_DIS         (CH5_CTL_PORT->BRR = CH5_CTL_PIN)

#define CH6_CTL_EN          (CH6_CTL_PORT->BSRR = CH6_CTL_PIN)
#define CH6_CTL_DIS         (CH6_CTL_PORT->BRR = CH6_CTL_PIN)


void bsp_InitGpio(void);

void LedToggle(void);

#endif

