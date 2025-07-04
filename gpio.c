/******************************************************************************
 *  File name:		gpio.c
 *  Date:			may 8 , 2025
 *******************************************************************************/

/*******************************************************************************
 *                        		Inclusions                                     *
 *******************************************************************************/
#include "stm32f103xx.h"
#include "gpio.h"

/*******************************************************************************
 *                      Private Definitions	                                   *
 *******************************************************************************/
#define GPIO_RESET_STATE            INPUT_FLOATING

/*******************************************************************************
 *                      Private Variables	                                   *
*******************************************************************************/
static u16 gau16_pin_initialization[INVALID_PORT_TYPE] = {0}; /* Each bit represent one pin in the specified port */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
/*******************************************************************************
 * Function Name:        gpio_init_pin
********************************************************************************/
s32 gpio_init_pin(tenu_pin_type enu_pin, tenu_mode_type enu_mode, tenu_status_type enu_status)
{
    s32 s32_ret = SUCCESS;
    tenu_pin_type enu_pin_number = enu_pin; // save the original value of enu_pin for later use
    
    if (enu_pin >= INVALID_PIN || enu_mode >= INVALID_MODE || enu_status >= INVALID_STATUS) // input validity
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        if(GET_BIT(gau16_pin_initialization[enu_pin_number / 16], enu_pin_number % 16) == 0) // check if the pin is already initialized
        {
            GPIO_RegDef_t *pstr_gpio_port;
        
            if (enu_pin <= 15)
            {
                pstr_gpio_port = GPIOA;
            }
            else if ((enu_pin >= 16) && (enu_pin <= 31))
            {
                pstr_gpio_port = GPIOB;
                enu_pin -= 16;
            }
            else
            {
                pstr_gpio_port = GPIOC;
                enu_pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
            }
            
            if (enu_pin <= 7)
            {
                if (enu_mode == INPUT_MODE)
                {
                    CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 0));
                    CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 1));
    
                    if (enu_status == INPUT_ANALOG)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else if (enu_status == INPUT_FLOATING)
                    {
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else if (enu_status == INPUT_PULL_UP)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                        SET_BIT(pstr_gpio_port->ODR, enu_pin);
                    }
                    else if (enu_status == INPUT_PULL_DOWN)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                        CLR_BIT(pstr_gpio_port->ODR, enu_pin);
                    }
                    else
                    {
                        s32_ret = ERROR_INVALID_ARGUMENTS;
                    }
                }
                else
                {
                    if (enu_mode == OUTPUT_MODE_10_MHZ)
                    {
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 0));
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 1));
                    }
                    else if (enu_mode == OUTPUT_MODE_2_MHZ)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 0));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 1));
                    }
                    else if (enu_mode == OUTPUT_MODE_50_MHZ)
                    {
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 0));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 1));
                    }
    
                    if (enu_status == OUTPUT_PUSH_PULL)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else if (enu_status == OUTPUT_OPEN_DRAIN)
                    {
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else if (enu_status == AF_PUSH_PULL)
                    {
                        CLR_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else if (enu_status == AF_OPEN_DRAIN)
                    {
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRL, (4 * enu_pin + 3));
                    }
                    else
                    {
                        s32_ret = ERROR_INVALID_ARGUMENTS;
                    }
                }
            }
            else
            {
                enu_pin -= 8; // enu_pin 8 appears in bit 0 in the CRH register
                if (enu_mode == INPUT_MODE)
                {
                    CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 0));
                    CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 1));
    
                    if (enu_status == INPUT_ANALOG)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else if (enu_status == INPUT_FLOATING)
                    {
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else if (enu_status == INPUT_PULL_UP)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                        SET_BIT(pstr_gpio_port->ODR, enu_pin);
                    }
                    else if (enu_status == INPUT_PULL_DOWN)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                        CLR_BIT(pstr_gpio_port->ODR, enu_pin);
                    }
                }
                else
                {
                    if (enu_mode == OUTPUT_MODE_10_MHZ)
                    {
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 0));
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 1));
                    }
                    else if (enu_mode == OUTPUT_MODE_2_MHZ)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 0));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 1));
                    }
                    else if (enu_mode == OUTPUT_MODE_50_MHZ)
                    {
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 0));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 1));
                    }
        
                    if (enu_status == OUTPUT_PUSH_PULL)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else if (enu_status == OUTPUT_OPEN_DRAIN)
                    {
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else if (enu_status == AF_PUSH_PULL)
                    {
                        CLR_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else if (enu_status == AF_OPEN_DRAIN)
                    {
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 2));
                        SET_BIT(pstr_gpio_port->CRH, (4 * enu_pin + 3));
                    }
                    else
                    {
                        s32_ret = ERROR_INVALID_ARGUMENTS;
                    }
                }
            }
        }
        else
        {
            s32_ret = ERROR_ALREADY_INITIALIZED; // pin is already initialized
        }
    }

    if (s32_ret == SUCCESS)
    {
        SET_BIT(gau16_pin_initialization[enu_pin_number / 16], enu_pin_number % 16); // set the bit in the array to indicate that the pin is initialized
    }
    return s32_ret;
}

/*******************************************************************************
 * Function Name:        gpio_write_pin
********************************************************************************/
s32 gpio_write_pin(tenu_pin_type enu_pin, tenu_pin_logic enu_pin_logic_state)
{
    s32 s32_ret = SUCCESS;
    if (enu_pin >= INVALID_PIN || enu_pin_logic_state >= INVALID_LOGIC)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        if(GET_BIT(gau16_pin_initialization[enu_pin / 16], enu_pin % 16))
        {
            GPIO_RegDef_t *pstr_gpio_port;

            if (enu_pin <= 15)
            {
                pstr_gpio_port = GPIOA;
            }
            else if ((enu_pin >= 16) && (enu_pin <= 31))
            {
                pstr_gpio_port = GPIOB;
                enu_pin -= 16;
            }
            else
            {
                pstr_gpio_port = GPIOC;
                enu_pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
            }

            if (enu_pin_logic_state == LOGIC_HIGH)
            {
                SET_BIT(pstr_gpio_port->ODR, enu_pin);
            }
            else
            {
                CLR_BIT(pstr_gpio_port->ODR, enu_pin);
            }
        }
        else
        {
            s32_ret = ERROR_NOT_INITIALIZED;
        }
    }

    return s32_ret;
}

/*******************************************************************************
 * Function Name:        gpio_read_pin
********************************************************************************/
s32 gpio_read_pin(tenu_pin_type enu_pin, tenu_pin_logic *penu_pin_logic_state)
{
    s32 s32_ret = SUCCESS;
    if (enu_pin >= INVALID_PIN || penu_pin_logic_state == NULL)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        if(GET_BIT(gau16_pin_initialization[enu_pin / 16], enu_pin % 16))
        {
            GPIO_RegDef_t *pstr_gpio_port;

            if (enu_pin <= 15)
            {
                pstr_gpio_port = GPIOA;
            }
            else if ((enu_pin >= 16) && (enu_pin <= 31))
            {
                pstr_gpio_port = GPIOB;
                enu_pin -= 16;
            }
            else
            {
                pstr_gpio_port = GPIOC;
                enu_pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
            }
            *penu_pin_logic_state = (tenu_pin_logic)GET_BIT(pstr_gpio_port->IDR, enu_pin);
        }
        else
        {
            s32_ret = ERROR_NOT_INITIALIZED;
        }
    }

    return s32_ret;
}

/*******************************************************************************
 * Function Name:        gpio_deinit_pin
********************************************************************************/
s32 gpio_deinit_pin(tenu_pin_type enu_pin)
{
    s32 s32_ret = SUCCESS;

    if (enu_pin >= INVALID_PIN)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        if(GET_BIT(gau16_pin_initialization[enu_pin / 16], enu_pin % 16)) // check if the pin is initialized
        {
            /* Clear the bit selection to be ab le to initialize it with the default state */
            CLR_BIT(gau16_pin_initialization[enu_pin / 16], enu_pin % 16);
            s32_ret = gpio_init_pin(enu_pin, INPUT_MODE, GPIO_RESET_STATE);
            if(SUCCESS != s32_ret)
            {
                /* set the bit again if the initialization with the reset value isn't applied successfully */
                SET_BIT(gau16_pin_initialization[enu_pin / 16], enu_pin % 16);
            }
        }
    }
    
    return s32_ret;
}
