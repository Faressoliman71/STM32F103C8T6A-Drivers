
/******************************************************************************
 *  File name:		nvic.c
 *  Date:			May 20, 2025
 *******************************************************************************/

/*******************************************************************************
 *                        		Inclusions                                     *
 *******************************************************************************/
#include "stm32f103xx.h"
#include "nvic.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*******************************************************************************
 * Function Name:        nvic_enable_irq
 * Description:          function to enable the IRQ
 * Parameters (in):     enu_nvic_irq
 * Parameters (out):     u32_state
 * Return value:         SUCCESS or ERROR
 ********************************************************************************/

s32 nvic_enable_irq(tenu_nvic_irq enu_nvic_irq)
{
    s32 s32_status = SUCCESS;

    if (enu_nvic_irq < INVALID_IRQn)
    {

        SET_BIT(NVIC->ISER[enu_nvic_irq / 32], enu_nvic_irq % 32);
    }
    else

    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_disable_irq
 * Description:          function to disable the IRQ
 * Parameters (in):     enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_disable_irq(tenu_nvic_irq enu_nvic_irq)
{
    s32 s32_status = SUCCESS;

    if (enu_nvic_irq < INVALID_IRQn)
    {

        SET_BIT(NVIC->ICER[enu_nvic_irq / 32], enu_nvic_irq % 32);
    }
    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_set_pending_irq
 * Description:          function to set the IRQ pending
 * Parameters (in):     enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_pending_irq(tenu_nvic_irq enu_nvic_irq)
{
    s32 s32_status = SUCCESS;

    if (enu_nvic_irq < INVALID_IRQn)
    {

        SET_BIT(NVIC->ISPR[enu_nvic_irq / 32], enu_nvic_irq % 32);
    }

    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_clear_pending_irq
 * Description:          function to clear the IRQ pending
 * Parameters (in):      enu_nvic_irq
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_clear_pending_irq(tenu_nvic_irq enu_nvic_irq)
{
    s32 s32_status = SUCCESS;

    if (enu_nvic_irq < INVALID_IRQn)
    {

        SET_BIT(NVIC->ICPR[enu_nvic_irq / 32], enu_nvic_irq % 32);
    }
    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_get_active_irq
 * Description:          function to get the active IRQ
 * Parameters (in):     penu_nvic_irq
 * Parameters (out):     u32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_get_active_irq(tenu_nvic_irq *penu_nvic_irq)
{
    s32 s32_status = SUCCESS;

    if (penu_nvic_irq != NULL)
    {
        *penu_nvic_irq = (tenu_nvic_irq)(NVIC->ISPR[0] | NVIC->ISPR[1]);
    }
    else
    {
        s32_status = ERROR_NULL_PTR;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_set_priority
 * Description:          function to set the IRQ priority
 * Parameters (in):      enu_nvic_irq, u8_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_priority(tenu_nvic_irq enu_nvic_irq, u8 u8_priority)
{
    s32 s32_status = SUCCESS;

    if ((enu_nvic_irq < INVALID_IRQn) && (u8_priority < 16))
    {
        // Calculate the register index and bit offset
        u8 reg_index = enu_nvic_irq / 4;
        u8 bit_pos = (enu_nvic_irq % 4) * 8;

        // Clear the existing priority bits
        NVIC->IPR[reg_index] &= ~(0xFF << bit_pos);

        // Set the new priority value (bits 7–4)
        NVIC->IPR[reg_index] |= (u8_priority << bit_pos);
    }
    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_get_priority
 * Description:          function to get the IRQ priority
 * Parameters (in):      enu_nvic_irq, pu8_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_get_priority(tenu_nvic_irq enu_nvic_irq, u8 *pu8_priority)
{
    s32 s32_status = SUCCESS;

    if ((pu8_priority) != NULL && (enu_nvic_irq < INVALID_IRQn))
    {

        // Calculate the register index and bit offset
        u8 reg_index = enu_nvic_irq / 4;
        u8 bit_pos = (enu_nvic_irq % 4) * 8;

        // Extract the 8-bit priority field and shift right by 4 to get the priority (bits 7–4)
        *pu8_priority = (NVIC->IPR[reg_index] >> bit_pos) & 0xFF; // Isolate 8-bit field
        *pu8_priority >>= 4;
    }
    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************
 * Function Name:        nvic_set_group_priority
 * Description:          function to set the IRQ group priority
 * Parameters (in):      tenu_group_priority
 * Parameters (out):     s32_state
 * Return value:         SUCCESS or ERROR
 * ********************************************************************************/
s32 nvic_set_group_priority(tenu_group_priority enu_group_priority)
{
    s32 s32_status = SUCCESS;

    if ((enu_group_priority <= SUBPRIORITY_4) && (enu_group_priority >= NO_SUBPRIORITY))
    {
        // Clear the group priority bits in the AIRCR register
        u32 u32_mask = 0X5FA << 16;
        SCB_AIRCR |= (u32_mask | (enu_group_priority << 8)); // Set the group priority bits
    }
    else
    {
        s32_status = ERROR_INVALID_ARGUMENTS;
    }

    return s32_status;
}
/*******************************************************************************/
