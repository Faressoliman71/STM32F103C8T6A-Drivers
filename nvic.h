
/******************************************************************************
 *  File name:       nvic.h
 *  Date:            May 20, 2025
 *******************************************************************************/
#ifndef NVIC_H
#define NVIC_H

/*******************************************************************************
 *                                Includes                                      *
 *******************************************************************************/
#include "common.h"

/*******************************************************************************
 *                                Data types                                      *
 *******************************************************************************/
typedef enum
{
    WWDG_IRQn = 0,
    PVD_IRQn = 1,
    TAMPER_IRQn = 2,
    RTC_IRQn = 3,
    FLASH_IRQn = 4,
    RCC_IRQn = 5,
    EXTI0_IRQn = 6,
    EXTI1_IRQn = 7,
    EXTI2_IRQn = 8,
    EXTI3_IRQn = 9,
    EXTI4_IRQn = 10,
    DMA1_Channel1_IRQn = 11,
    DMA1_Channel2_IRQn = 12,
    DMA1_Channel3_IRQn = 13,
    DMA1_Channel4_IRQn = 14,
    DMA1_Channel5_IRQn = 15,
    DMA1_Channel6_IRQn = 16,
    DMA1_Channel7_IRQn = 17,
    ADC1_2_IRQn = 18,
    USB_HP_CAN_TX_IRQn = 19,
    USB_LP_CAN_RX0_IRQn = 20,
    CAN_RX1_IRQn = 21,
    CAN_SCE_IRQn = 22,
    EXTI9_5_IRQn = 23,
    TIM1_BRK_IRQn = 24,
    TIM1_UP_IRQn = 25,
    TIM1_TRG_COM_IRQn = 26,
    TIM1_CC_IRQn = 27,
    TIM2_IRQn = 28,
    TIM3_IRQn = 29,
    TIM4_IRQn = 30,
    I2C1_EV_IRQn = 31,
    I2C1_ER_IRQn = 32,
    SPI1_IRQn = 35,
    SPI2_IRQn = 36,
    USART1_IRQn = 37,
    USART2_IRQn = 38,
    USART3_IRQn = 39,
    EXTI15_10_IRQn = 40,
    RTC_Alarm_IRQn = 41,
    USBWakeUp_IRQn = 42,
    TIM8_BRK_IRQn = 43,
    TIM8_UP_IRQn = 44,
    TIM8_TRG_COM_IRQn = 45,
    TIM8_CC_IRQn = 46,
    ADC3_IRQn = 47,
    FSMC_IRQn = 48,
    SDIO_IRQn = 49,
    TIM5_IRQn = 50,
    SPI3_IRQn = 51,
    UART4_IRQn = 52,
    UART5_IRQn = 53,
    TIM6_IRQn = 54,
    TIM7_IRQn = 55,
    DMA2_Channel1_IRQn = 56,
    DMA2_Channel2_IRQn = 57,
    DMA2_Channel3_IRQn = 58,
    DMA2_Channel4_IRQn = 59,
    INVALID_IRQn = 60

} tenu_nvic_irq;

typedef enum
{
    NO_SUBPRIORITY = 0b011,
    SUBPRIORITY_1 = 0b100, // bit 4
    SUBPRIORITY_2 = 0b101, // bit 4 ,5
    SUBPRIORITY_3 = 0b110,
    SUBPRIORITY_4 = 0b111

} tenu_group_priority;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*******************************************************************************
 * Function Name:        nvic_enable_irq
 * Description:          function to enable the IRQ
 * Parameters (in):      enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 ********************************************************************************/
s32 nvic_enable_irq(tenu_nvic_irq enu_nvic_irq);
/*******************************************************************************
 * Function Name:        nvic_disable_irq
 * Description:          function to disable the IRQ
 * Parameters (in):      enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_disable_irq(tenu_nvic_irq enu_nvic_irq);
/*******************************************************************************
 * Function Name:        nvic_set_pending_irq
 * Description:          function to set the IRQ pending
 * Parameters (in):      enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_pending_irq(tenu_nvic_irq enu_nvic_irq);
/*******************************************************************************
 * Function Name:        nvic_clear_pending_irq
 * Description:          function to clear the IRQ pending
 * Parameters (in):      enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_clear_pending_irq(tenu_nvic_irq enu_nvic_irq);
/*******************************************************************************
 * Function Name:        nvic_get_active_irq
 * Description:          function to get the active IRQ
 * Parameters (in):      penu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_get_active_irq(tenu_nvic_irq *penu_nvic_irq);
/*******************************************************************************
 * Function Name:        nvic_set_priority
 * Description:          function to set the IRQ priority
 * Parameters (in):      enu_nvic_irq, u8_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_priority(tenu_nvic_irq enu_nvic_irq, u8 u8_priority);
/*******************************************************************************
 * Function Name:        nvic_get_priority
 * Description:          function to get the IRQ priority
 * Parameters (in):     enu_nvic_irq, pu8_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_get_priority(tenu_nvic_irq enu_nvic_irq, u8 *pu8_priority);
/*******************************************************************************
 * Function Name:        nvic_set_group_priority
 * Description:          function to set the IRQ group priority
 * Parameters (in):      tenu_group_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_group_priority(tenu_group_priority enu_group_priority);

#endif
