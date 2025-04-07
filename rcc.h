/****************************************************************
* Author : Fares Soliman
* Date :  2 April 2025
* Name : rcc.h
* version : 1
*****************************************************************/

#ifndef RCC_H
#define RCC_H



/*********************INCLUDES***********************************/

#include "common.h"

/************************AHB Peripherals**************************/

#define RCC_AHB_OFFSET     0
#define RCC_DMA1           0
#define RCC_DMA2           1
#define RCC_SRAM           2
#define RCC_FLITF          4
#define RCC_CRC            6
#define RCC_FSMC           8
#define RCC_SDIO           9

 /*******************************************************************************
 *                                APB2 Peripherals                              *
 *******************************************************************************/
 #define RCC_APB2_OFFSET          (32)
 #define RCC_AFI                  (0  + RCC_APB2_OFFSET)
 #define RCC_GPIOA                (2  + RCC_APB2_OFFSET)
 #define RCC_GPIOB                (3  + RCC_APB2_OFFSET)
 #define RCC_GPIOC                (4  + RCC_APB2_OFFSET)
 #define RCC_GPIOD                (5  + RCC_APB2_OFFSET)
 #define RCC_GPIOE                (6  + RCC_APB2_OFFSET)
 #define RCC_GPIOF                (7  + RCC_APB2_OFFSET)
 #define RCC_GPIOG                (8  + RCC_APB2_OFFSET)
 #define RCC_ADC1                 (9  + RCC_APB2_OFFSET)
 #define RCC_ADC2                 (10 + RCC_APB2_OFFSET)
 #define RCC_TIM1                 (11 + RCC_APB2_OFFSET)
 #define RCC_SPI1                 (12 + RCC_APB2_OFFSET)
 #define RCC_TIM8                 (13 + RCC_APB2_OFFSET)
 #define RCC_USART1               (14 + RCC_APB2_OFFSET)
 #define RCC_ADC3                 (15 + RCC_APB2_OFFSET)
 #define RCC_TIM9                 (19 + RCC_APB2_OFFSET)
 #define RCC_TIM10                (20 + RCC_APB2_OFFSET)
 #define RCC_TIM11                (21 + RCC_APB2_OFFSET)

 /*******************************************************************************
 *                                APB1 Peripherals                              *
 *******************************************************************************/
 #define RCC_APB1_OFFSET          (64)
 #define RCC_TIM2                 (0  + RCC_APB1_OFFSET)
 #define RCC_TIM3                 (1  + RCC_APB1_OFFSET)
 #define RCC_TIM4                 (2  + RCC_APB1_OFFSET)
 #define RCC_TIM5                 (3  + RCC_APB1_OFFSET)
 #define RCC_TIM6                 (4  + RCC_APB1_OFFSET)
 #define RCC_TIM7                 (5  + RCC_APB1_OFFSET)
 #define RCC_TIM12                (6  + RCC_APB1_OFFSET)
 #define RCC_TIM13                (7  + RCC_APB1_OFFSET)
 #define RCC_TIM14                (8  + RCC_APB1_OFFSET)
 #define RCC_WWD                  (11 + RCC_APB1_OFFSET)
 #define RCC_SPI2                 (14 + RCC_APB1_OFFSET)
 #define RCC_SPI3                 (15 + RCC_APB1_OFFSET)
 #define RCC_USART2               (17 + RCC_APB1_OFFSET)
 #define RCC_USART3               (18 + RCC_APB1_OFFSET)
 #define RCC_USART4               (19 + RCC_APB1_OFFSET)
 #define RCC_USART5               (20 + RCC_APB1_OFFSET)
 #define RCC_I2C1                 (21 + RCC_APB1_OFFSET)
 #define RCC_I2C2                 (22 + RCC_APB1_OFFSET)
 #define RCC_USB                  (23 + RCC_APB1_OFFSET)
 #define RCC_CAN                  (25 + RCC_APB1_OFFSET)
 #define RCC_BKP                  (27 + RCC_APB1_OFFSET)
 #define RCC_PWR                  (28 + RCC_APB1_OFFSET)
 #define RCC_DAC                  (29 + RCC_APB1_OFFSET)

 #define RCC_INVALID_PERIPHERAL   (RCC_DAC + 1)
 
 /******************************* Function ProtoTypes **********************/
 
 
/***************************************************************************
Function : rcc_init_system_clock
Description : function to init system clock source
Parameters(in) : void
Parmeters(out) : s32
Return : SUCCESS or ERROR
****************************************************************************/
 
 s32 rcc_init_system_clock(void);
 
 /***************************************************************************
 Function : rcc_enable_disable_peripheral
 Description : function to enable/disable peripheral clock
 Parameters(in) : u8_peripheral , b_state
 Parmeters(out) : s32
 Return : SUCCESS or ERROR
 *****************************************************************************/
 
 s32 rcc_enable_disable_peripheral(u8 u8_peripheral , bool b_state);
 
 
 #endif