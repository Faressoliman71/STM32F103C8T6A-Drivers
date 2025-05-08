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
#define GPIO_RESET_STATE INPUT_FLOATING

/*******************************************************************************
 *                      Private Variables	                                   *
 *******************************************************************************/



/************************************************/

s32 gpio_init_pin(enu_pin_type pin, enu_mode_type mode, enu_status_type status)
{
    s32 s32_ret = SUCCESS;
    if (pin >= INVALID_PIN || mode >= INVALID_MODE || status >= INVALID_STATUS) // input validity
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        GPIO_RegDef_t *pstr_gpio_port;

        if ((pin >= 0) && (pin <= 15))
        {
            pstr_gpio_port = GPIOA;
        }
        else if ((pin >= 16) && (pin <= 31))
        {
            pstr_gpio_port = GPIOB;
            pin -= 16;
        }
        else
        {
            pstr_gpio_port = GPIOC;
            pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
        }

        if (pin <= 7)
        {
            if (mode == INPUT_MODE)
            {

                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 0);
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 1);

                if (status == INPUT_ANALOG)
                {
                    CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                    CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
                }
                else if (status == INPUT_FLOATING)
                {
                    SET_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                    CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
                }
                else if (status == INPUT_PULL_UP)
                {
                    CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                    SET_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
                    SET_BIT(pstr_gpio_port->ODR, pin);
                }
                else if (status == INPUT_PULL_DOWN)
                {
                    CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                    SET_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
                    CLR_BIT(pstr_gpio_port->ODR, pin);
                }
            }
            else if (mode == OUTPUT_MODE_10_MHZ)
            {
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 0);
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 1);
            }
            else if (mode == OUTPUT_MODE_2_MHZ)
            {
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 0);
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 1);
            }
            else if (mode == OUTPUT_MODE_50_MHZ)
            {
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 0);
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 1);
            }
            if (status == OUTPUT_PUSH_PULL)
            {
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
            }
            else if (status == OUTPUT_OPEN_DRAIN)
            {
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
            }
            else if (status == AF_PUSH_PULL)
            {
                CLR_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
            }
            else if (status == AF_OPEN_DRAIN)
            {
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 2);
                SET_BIT(pstr_gpio_port->CRL, 4 * pin + 3);
            }
        }
        else
        {
            pin -= 8; // pin 8 appears in bit 0 in the CRH register
            if (mode == INPUT_MODE)
            {
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 0);
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 1);

                if (status == INPUT_ANALOG)
                {
                    CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                    CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
                }
                else if (status == INPUT_FLOATING)
                {
                    SET_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                    CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
                }
                else if (status == INPUT_PULL_UP)
                {
                    CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                    SET_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
                    SET_BIT(pstr_gpio_port->ODR, pin);
                }
                else if (status == INPUT_PULL_DOWN)
                {
                    CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                    SET_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
                    CLR_BIT(pstr_gpio_port->ODR, pin);
                }
            }
            else if (mode == OUTPUT_MODE_10_MHZ)
            {
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 0);
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 1);
            }
            else if (mode == OUTPUT_MODE_2_MHZ)
            {
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 0);
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 1);
            }
            else if (mode == OUTPUT_MODE_50_MHZ)
            {
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 0);
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 1);
            }

            if (status == OUTPUT_PUSH_PULL)
            {
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
            }
            else if (status == OUTPUT_OPEN_DRAIN)
            {
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
            }
            else if (status == AF_PUSH_PULL)
            {
                CLR_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
            }
            else if (status == AF_OPEN_DRAIN)
            {
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 2);
                SET_BIT(pstr_gpio_port->CRH, 4 * pin + 3);
            }
        }
    }

    return s32_ret;
}

s32 gpio_write_pin(enu_pin_type pin, enu_pin_logic enu_pin_logic_state)
{
    s32 s32_ret = SUCCESS;
    if (pin >= INVALID_PIN || enu_pin_logic_state >= INVALID_LOGIC)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {

        GPIO_RegDef_t *pstr_gpio_port;

        if ((pin >= 0) && (pin <= 15))
        {
            pstr_gpio_port = GPIOA;
        }
        else if ((pin >= 16) && (pin <= 31))
        {
            pstr_gpio_port = GPIOB;
            pin -= 16;
        }
        else
        {
            pstr_gpio_port = GPIOC;
            pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
        }

        if (enu_pin_logic_state == LOGIC_HIGH)
        {
            SET_BIT(pstr_gpio_port->ODR, pin);
        }
        else
        {
            CLR_BIT(pstr_gpio_port->ODR, pin);
        }
    }

    return s32_ret;
}

s32 gpio_read_pin(enu_pin_type pin, enu_pin_logic *penu_pin_logic_state)
{
    s32 s32_ret = SUCCESS;
    if (pin >= INVALID_PIN || penu_pin_logic_state == NULL)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    else
    {

        GPIO_RegDef_t *pstr_gpio_port;

        if ((pin >= 0) && (pin <= 15))
        {
            pstr_gpio_port = GPIOA;
        }
        else if ((pin >= 16) && (pin <= 31))
        {
            pstr_gpio_port = GPIOB;
            pin -= 16;
        }
        else
        {
            pstr_gpio_port = GPIOC;
            pin -= 19; // blue pill have only 3 pins in portc c13 , c14 , c15
        }
        *penu_pin_logic_state = (enu_pin_logic)GET_BIT(pstr_gpio_port->IDR, pin);
    }

    return s32_ret;
}

s32 gpio_deinit_pin(enu_pin_type enu_pin)
{
    s32 s32_ret = SUCCESS;

    s32_ret = gpio_init_pin(enu_pin, INPUT_MODE, GPIO_RESET_STATE);
    if (enu_pin >= INVALID_PIN)
    {
        s32_ret = ERROR_INVALID_ARGUMENTS;
    }
    return s32_ret;
}
