/******************************************************************************
*  File name:		afio.h
*  Date:			Apr 19, 2025
*******************************************************************************/
#ifndef AFIO_H_
#define AFIO_H_

/*******************************************************************************
*                                Includes                                      *
*******************************************************************************/
#include "common.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/
/*******************************************************************************
*                       	   		AFIO PORTS                 	               *
*******************************************************************************/
#define AFIO_PORTA							(0)
#define AFIO_PORTB							(1)
#define AFIO_PORTC							(2)
#define AFIO_PORTD							(3)
#define AFIO_PORTE							(4)
#define AFIO_INVALID_PORT                   (5)

/*******************************************************************************
*                       	   		AFIO EXTI LINE                 	           *
*******************************************************************************/
#define AFIO_EXTI_LINE0						(0)
#define AFIO_EXTI_LINE1						(1)
#define AFIO_EXTI_LINE2						(2)
#define AFIO_EXTI_LINE3						(3)
#define AFIO_EXTI_LINE4						(4)
#define AFIO_EXTI_LINE5						(5)
#define AFIO_EXTI_LINE6						(6)
#define AFIO_EXTI_LINE7						(7)
#define AFIO_EXTI_LINE8						(8)
#define AFIO_EXTI_LINE9						(9)
#define AFIO_EXTI_LINE10					(10)
#define AFIO_EXTI_LINE11					(11)
#define AFIO_EXTI_LINE12					(12)
#define AFIO_EXTI_LINE13					(13)
#define AFIO_EXTI_LINE14					(14)
#define AFIO_EXTI_LINE15					(15)
#define AFIO_INVALID_EXTI_LINE              (16)

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/
/*******************************************************************************
* Name: tenu_afio_uart_remap
* Description: Data type to initialize the UART
********************************************************************************/
typedef enum
{
	AFIO_UART1_Tx_PA9_Rx_PA10,
    AFIO_UART1_Tx_PB6_Rx_PB7,
    AFIO_UART2_Tx_PA2_Rx_PA3,
    AFIO_UART2_Tx_PD5_Rx_PD6,
    AFIO_UART3_Tx_PB10_Rx_PB11,
    AFIO_UART3_Tx_PC10_Rx_PC11,
    AFIO_UART3_Tx_PD8_Rx_PD9
}tenu_afio_uart_remap;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		afio_set_exti_source
* Description:			Function to set the port source of EXTIx
* Parameters (in):    	The EXTI number
* 						The required Port
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 afio_set_exti_source(u8 u8_exti_line , u8 u8_port);

/*******************************************************************************
* Function Name:		afio_disable_jtag
* Description:			Function to disable JTAG
* Parameters (in):    	void
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 afio_disable_jtag(void);

/*******************************************************************************
* Function Name:		afio_set_uart_remap
* Description:			Function to remap the UART pins
* Parameters (in):    	The UART Re-map we want
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 afio_set_uart_remap(tenu_afio_uart_remap enu_afio_uart_remap_value);

#endif
