/******************************************************************************
*  File name:       uart.h
*  Date:            Apr 18, 2025
*******************************************************************************/

#ifndef UART_H_
#define UART_H_

/*******************************************************************************
*                                Includes                                      *
*******************************************************************************/
#include "common.h"

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: tstr_uart_config
* Description: Data type to initialize the UART
********************************************************************************/
typedef struct
{
	u32 u32_baud_rate; /* Baud rate */
	u8 u8_stop_bit;
	u8 u8_data_size;
	u8 u8_parity;
	u8 u8_receive_method; 
}tstr_uart_config;

/*******************************************************************************
* Name: tstr_uart_config
* Description: Data type to initialize the UART
********************************************************************************/
typedef void(*pf_uart_callback)(u16);

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   	UART CHANNELS		                	       *
*******************************************************************************/
#define UART_1								(0)
#define UART_2								(1)
#define UART_3								(2)
#define TOTAL_UART_CHANNELS					(3)

/*******************************************************************************
*                       	   	STOP BITS		   		                       *
*******************************************************************************/
#define UART_STOP_1_BIT						(0b00)
#define UART_STOP_0_5_BIT					(0b01)
#define UART_STOP_2_BITS					(0b10)
#define UART_STOP_1_5_BITS					(0b11)

/*******************************************************************************
*                       	   	DATA SIZE		                	           *
*******************************************************************************/
#define UART_8_BITS							(0)
#define UART_9_BITS							(1)

/*******************************************************************************
*                       	   	PARTIY		   		             	           *
*******************************************************************************/
#define UART_PARITY_DISABLED				(0b00)
#define UART_PARITY_EVEN					(0b10)
#define UART_PARITY_ODD						(0b11)

/*******************************************************************************
*                       	   	RECEIVE METHOD		                	       *
*******************************************************************************/
#define UART_RX_POLLING						(0b000) /* DMA disabled, send and receive with poling */
#define UART_RX_INTERRUPT					(0b001) /* DMA disabled, send with polling and receive with interrupt */
#define UART_RX_POLLING_TX_DMA				(0b100) /* Send with DMA receive with polling */
#define UART_RX_INTERRUPT_TX_DMA			(0b101) /* Send with DMA receive with interrupt */
#define UART_RX_DMA							(0b010) /* Receive with DMA send with polling */
#define UART_RX_DMA_TX_DMA					(0b110) /* Send with DMA receive with DMA */
#define UART_RX_DISABLED					(0b111) /* Send with polling, Receive disabled */

/*******************************************************************************
*                       Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		uart_init
* Description:			Function to initialize the UART
* Parameters (in):    	Pointer to structure of type UART_RegDef_t
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 uart_init(u8 u8_uart_channel, tstr_uart_config * str_uart_configuration);

/*******************************************************************************
* Function Name:		uart_send_byte
* Description:			Function to send one byte using the UART
* Parameters (in):    	Data Byte
* Parameters (in):    	Data Size
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 uart_send(u8 u8_uart_channel, u8* pu8_data, u16 u16_data_size);

/*******************************************************************************
* Function Name:		uart_receive_byte
* Description:			Function to receive one byte using UART
* Parameters (in):    	Pointer to variable to save the data on it
* Parameters (in):    	Data Size
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 uart_receive(u8 u8_uart_channel, u8* pu8_data, u16 u16_data_size);

/*******************************************************************************
* Function Name:		UART_u8SetCallBack
* Description:			Function to set the ISR
* Parameters (in):    	Pointer to function to act as the ISR
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 uart_set_callback(u8 u8_uart_channel, pf_uart_callback pf_uart_cb);

/*******************************************************************************
* Function Name:		uart_deinit
* Description:			Function to de-initialize the UART
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 uart_deinit(u8 u8_uart_channel);

#endif /* UART_H_ */

