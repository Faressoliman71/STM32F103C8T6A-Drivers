/******************************************************************************
*  File name:		uart.c
*  Date:            Apr 18, 2025
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "stm32f103xx.h"
#include "uart.h"

/*******************************************************************************
*                      Defines                                                 *
*******************************************************************************/
#define UART_MAX_TIMEOUT		(0xFFFFFF)

/*******************************************************************************
*                      Private Variables	                                   *
*******************************************************************************/
static UART_RegDef_t *const gastr_uart[TOTAL_UART_CHANNELS] = {UART1, UART2, UART3};
static pf_uart_callback gapf_uart_cb[TOTAL_UART_CHANNELS] = {NULL, NULL, NULL};
static u8 gu8_uart_initialization = 0;

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		uart_init
********************************************************************************/
s32 uart_init(u8 u8_uart_channel, tstr_uart_config * str_uart_configuration)
{
	s32 s32_return = ERROR;

	if((NULL != str_uart_configuration) && (TOTAL_UART_CHANNELS > u8_uart_channel))
	{
        if(GET_BIT(gu8_uart_initialization, u8_uart_channel) == 0)
        {
            gastr_uart[u8_uart_channel]->CR1 = 0;
            gastr_uart[u8_uart_channel]->CR2 = 0;
            gastr_uart[u8_uart_channel]->CR3 = 0;
            
            gastr_uart[u8_uart_channel]->CR1 |= ((str_uart_configuration->u8_data_size & 0b1) << 12);
            gastr_uart[u8_uart_channel]->CR1 |= ((str_uart_configuration->u8_parity & 0b11) << 9);
            
            if(UART_RX_DISABLED != str_uart_configuration->u8_receive_method)
            {
                /* First bit indicates the receive is interrupt or polling */
                gastr_uart[u8_uart_channel]->CR1 |= ((str_uart_configuration->u8_receive_method & 0b1) << 5);
                
                /* Second and third bit indicates the DMA Configuration */
                gastr_uart[u8_uart_channel]->CR3 |= (((str_uart_configuration->u8_receive_method >> 1) & 0b11) << 6);
                gastr_uart[u8_uart_channel]->CR2 |= ((str_uart_configuration->u8_stop_bit & 0b11) << 12);
            }

            /* Baud Rate Calculations */
            u16 u16_mantissa = (F_CPU / (16 * str_uart_configuration->u32_baud_rate));
            u16 u16_fraction = ((F_CPU % (16 * str_uart_configuration->u32_baud_rate)) / str_uart_configuration->u32_baud_rate );
            f32 Reminder = (F_CPU - u16_mantissa * 16 * str_uart_configuration->u32_baud_rate) / (float)str_uart_configuration->u32_baud_rate;
            if(((Reminder - (int)Reminder)*10)  >= 5)
            {
                u16_fraction ++;
                if(u16_fraction > 15)
                {
                    u16_fraction = 0;
                    u16_mantissa ++;
                }
            }
            gastr_uart[u8_uart_channel]->BRR = ((u16_mantissa & 0xFFF) << 4) | (u16_fraction & 0xF);

            SET_BIT(gastr_uart[u8_uart_channel]->CR1, 3); /* Transmit Enable */
            if(UART_RX_DISABLED != str_uart_configuration->u8_receive_method)
            {
                SET_BIT(gastr_uart[u8_uart_channel]->CR1, 2); /* Receive Enable */
            }
            SET_BIT(gastr_uart[u8_uart_channel]->CR1, 13); /* Enable the UART */
            
            SET_BIT(gu8_uart_initialization, u8_uart_channel);
            s32_return = SUCCESS;
        }
        else
        {
            s32_return = ERROR_ALREADY_INITIALIZED;
        }
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}

	return s32_return;
}

/*******************************************************************************
* Function Name:		uart_send
********************************************************************************/
s32 uart_send(u8 u8_uart_channel, u8* pu8_data, u16 u16_data_size)
{
	s32 s32_return = ERROR;

	if((NULL != pu8_data) && (u16_data_size > 0) && (TOTAL_UART_CHANNELS > u8_uart_channel))
	{
        if(GET_BIT(gu8_uart_initialization, u8_uart_channel))
        {
            for(u16 u16_idx = 0; u16_idx < u16_data_size; u16_idx++)
            {
                u32 u32_max_timeout_loop = UART_MAX_TIMEOUT;
                
                /* Wait if the previous Transmission isn't completed */
                while((GET_BIT(gastr_uart[u8_uart_channel]->SR, 7) == 0) && (u32_max_timeout_loop > 0))
                {
                    u32_max_timeout_loop--;
                }

                if(u32_max_timeout_loop > 0)
                {
                    gastr_uart[u8_uart_channel]->DR = pu8_data[u16_idx]; /* The flag is cleared when we write to the data register */

                    /* Wait if the previous Transmission isn't completed */
                    while((GET_BIT(gastr_uart[u8_uart_channel]->SR, 6) == 0) && (u32_max_timeout_loop > 0))
                    {
                        u32_max_timeout_loop--;
                    }

                    if(u32_max_timeout_loop > 0)
                    {
                        s32_return = SUCCESS;
                    }
                    else
                    {
                        s32_return = ERROR_TIMEOUT;
                        break;
                    }
                }
                else
                {
                    s32_return = ERROR_TIMEOUT;
                    break;
                }
            }
            s32_return = SUCCESS;
        }
        else
        {
            s32_return = ERROR_NOT_INITIALIZED;
        }
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}
	
	return s32_return;
}

/*******************************************************************************
* Function Name:		uart_receive
********************************************************************************/
s32 uart_receive(u8 u8_uart_channel, u8* pu8_data, u16 u16_data_size)
{
	s32 s32_return = ERROR;

	if((NULL != pu8_data) && (u16_data_size > 0) && (TOTAL_UART_CHANNELS > u8_uart_channel))
	{
        if(GET_BIT(gu8_uart_initialization, u8_uart_channel))
        {
            for(u16 u16_idx = 0; u16_idx < u16_data_size; u16_idx++)
            {
                u32 u32_max_timeout_loop = UART_MAX_TIMEOUT;
                while((GET_BIT(gastr_uart[u8_uart_channel]->SR, 5) == 0) && (u32_max_timeout_loop > 0))
                {
                    u32_max_timeout_loop--;
                }

                if(u32_max_timeout_loop > 0)
                {
                    s32_return = SUCCESS;
                    pu8_data[u16_idx] = gastr_uart[u8_uart_channel]->DR;
                    CLR_BIT(gastr_uart[u8_uart_channel]->SR, 5); /* Clear the flag */
                }
                else
                {
                    s32_return = ERROR_TIMEOUT;
                    break;
                }
            }
        }
        else
        {
            s32_return = ERROR_NOT_INITIALIZED;
        }
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}

	return s32_return;
}

/*******************************************************************************
* Function Name:		uart_set_callback
********************************************************************************/
s32 uart_set_callback(u8 u8_uart_channel, pf_uart_callback pf_uart_cb)
{
	s32 s32_return = ERROR;

	if((pf_uart_cb != NULL) && (TOTAL_UART_CHANNELS > u8_uart_channel))
	{
		s32_return = SUCCESS;
		gapf_uart_cb[u8_uart_channel] = pf_uart_cb;
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}

	return s32_return;
}

/*******************************************************************************
* Function Name:		uart_deinit
********************************************************************************/
s32 uart_deinit(u8 u8_uart_channel)
{
    s32 s32_return = ERROR;

    if(TOTAL_UART_CHANNELS > u8_uart_channel)
	{
        /* Clear the used registers in the init function */
        gastr_uart[u8_uart_channel]->CR1 = 0;
		gastr_uart[u8_uart_channel]->CR2 = 0;
        gastr_uart[u8_uart_channel]->CR3 = 0;
        gastr_uart[u8_uart_channel]->BRR = 0;
        
        /* Clear the callback*/
		gapf_uart_cb[u8_uart_channel] = NULL;
		
        /* Clear the initialization flag */
        CLR_BIT(gu8_uart_initialization, u8_uart_channel);
        
		s32_return = SUCCESS;
	}
	else
	{
		s32_return = ERROR_INVALID_ARGUMENTS;
	}

    return s32_return;
}

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void USART1_IRQHandler(void)
{
	CLR_BIT(UART1->SR, 5); /* Clear the flag */
	if(gapf_uart_cb[UART_1] != NULL)
	{
		gapf_uart_cb[UART_1](gastr_uart[UART_1]->DR);
	}
}

void USART2_IRQHandler(void)
{
	CLR_BIT(UART2->SR, 5); /* Clear the flag */
	if(gapf_uart_cb[UART_2] != NULL)
	{
		gapf_uart_cb[UART_2](gastr_uart[UART_2]->DR);
	}
}

void USART3_IRQHandler(void)
{
	CLR_BIT(UART3->SR, 5); /* Clear the flag */
	if(gapf_uart_cb[UART_3] != NULL)
	{
		gapf_uart_cb[UART_3](gastr_uart[UART_3]->DR);
	}
}

