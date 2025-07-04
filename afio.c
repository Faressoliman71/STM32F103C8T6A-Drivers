/******************************************************************************
*  File name:		afio.c
*  Date:			Apr 19, 2025
*******************************************************************************/
#include "stm32f103xx.h"
#include "afio.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		AFIO_u8SetEXTIPortSource
********************************************************************************/

s32 afio_set_exti_source(u8 u8_exti_line , u8 u8_port)
{
	s32 s32_return = ERROR;

	if(u8_exti_line < AFIO_INVALID_EXTI_LINE && u8_port < AFIO_INVALID_PORT)
	{
		u8 u8_register_number = u8_exti_line / 4;
		u8 u8_byte_number = u8_exti_line % 4;

		AFIO->EXTICR[u8_register_number] &= ~(0b1111 << (4*u8_byte_number));
		AFIO->EXTICR[u8_register_number] |= (u8_port << (4*u8_byte_number));

		s32_return = SUCCESS;
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}

	return s32_return;
}

/*******************************************************************************
* Function Name:		AFIO_u8DisableJTAG
********************************************************************************/
s32 afio_disable_jtag(void)
{
	s32 s32_return = SUCCESS;

	CLR_BIT(AFIO->MAPR, 26);
	SET_BIT(AFIO->MAPR, 25);
	CLR_BIT(AFIO->MAPR, 24);

	return s32_return;
}

/*******************************************************************************
* Function Name:		AFIO_u8SetUARTConfiguration
********************************************************************************/
s32 afio_set_uart_remap(tenu_afio_uart_remap enu_afio_uart_remap_value)
{
	s32 s32_return = SUCCESS;

	switch(enu_afio_uart_remap_value)
	{
		case AFIO_UART1_Tx_PA9_Rx_PA10:
		{
			WRITE_BIT(AFIO->MAPR, 2, 0);
			break;
		}
		case AFIO_UART1_Tx_PB6_Rx_PB7:
		{
			WRITE_BIT(AFIO->MAPR, 2, 1);
			break;
		}
		case AFIO_UART2_Tx_PA2_Rx_PA3:
		{
			WRITE_BIT(AFIO->MAPR, 3, 0);
			break;
		}
		case AFIO_UART2_Tx_PD5_Rx_PD6:
		{
			WRITE_BIT(AFIO->MAPR, 3, 1);
			break;
		}
		case AFIO_UART3_Tx_PB10_Rx_PB11:
		{
			WRITE_BIT(AFIO->MAPR, 4, 0);
			WRITE_BIT(AFIO->MAPR, 5, 0);
			break;
		}
		case AFIO_UART3_Tx_PC10_Rx_PC11:
		{
			WRITE_BIT(AFIO->MAPR, 4, 1);
			WRITE_BIT(AFIO->MAPR, 5, 0);
			break;
		}
		case AFIO_UART3_Tx_PD8_Rx_PD9:
		{
			WRITE_BIT(AFIO->MAPR, 4, 1);
			WRITE_BIT(AFIO->MAPR, 5, 1);
			break;
		}
		default:
		{
			s32_return = ERROR_INVALID_ARGUMENTS;
			break;
		}
	}

	return s32_return;
}
