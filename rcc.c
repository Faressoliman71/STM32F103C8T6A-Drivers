/******************************************************************************
*  File name:		rcc.c
*  Date:			Mar 7, 2025
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "stm32f103xx.h"
#include "rcc.h"

/*******************************************************************************
*                           Local Definitions                                  *
*******************************************************************************/
#define MAX_TIMEOUT                         100000

/*******************************************************************************
*                        		Clock Source	                               *
*******************************************************************************/
#define RCC_u8_HSI	1
#define RCC_u8_HSE	2
#define RCC_u8_PLL	3

/*******************************************************************************
*                        		PLL Clock Source	                           *
*******************************************************************************/
#define RCC_u8_PLL_HSI_DIVIDED_BY_2			1
#define RCC_u8_PLL_HSE						2
#define RCC_u8_PLL_HSE_DIVIDED_BY_2			3

/*******************************************************************************
*                        		PLL Clock Multiplier	                       *
*******************************************************************************/
#define RCC_u8_PLL_MULTIPLY_BY_2 			0b0000
#define RCC_u8_PLL_MULTIPLY_BY_3 			0b0001
#define RCC_u8_PLL_MULTIPLY_BY_4 			0b0010
#define RCC_u8_PLL_MULTIPLY_BY_5 			0b0011
#define RCC_u8_PLL_MULTIPLY_BY_6 			0b0100
#define RCC_u8_PLL_MULTIPLY_BY_7 			0b0101
#define RCC_u8_PLL_MULTIPLY_BY_8 			0b0110
#define RCC_u8_PLL_MULTIPLY_BY_9 			0b0111
#define RCC_u8_PLL_MULTIPLY_BY_10			0b1000
#define RCC_u8_PLL_MULTIPLY_BY_11			0b1001
#define RCC_u8_PLL_MULTIPLY_BY_12			0b1010
#define RCC_u8_PLL_MULTIPLY_BY_13			0b1011
#define RCC_u8_PLL_MULTIPLY_BY_14			0b1100
#define RCC_u8_PLL_MULTIPLY_BY_15			0b1101
#define RCC_u8_PLL_MULTIPLY_BY_16			0b1110

/*******************************************************************************
*                        		HSE Clock Source	                           *
*******************************************************************************/
#define RCC_u8_HSE_NOT_BYPASS					1
#define RCC_u8_HSE_BYPASS						2

/*******************************************************************************
*                        		ADC Prescaler		                           *
*******************************************************************************/
#define RCC_u8_ADC_DIVIDED_BY_2						0b00
#define RCC_u8_ADC_DIVIDED_BY_4						0b01
#define RCC_u8_ADC_DIVIDED_BY_6						0b10
#define RCC_u8_ADC_DIVIDED_BY_8						0b11

/*******************************************************************************
*                        		APBx Prescaler		                           *
*******************************************************************************/
#define RCC_u8_APBx_DIVIDED_BY_1					0b000
#define RCC_u8_APBx_DIVIDED_BY_2					0b100
#define RCC_u8_APBx_DIVIDED_BY_4					0b101
#define RCC_u8_APBx_DIVIDED_BY_8					0b110
#define RCC_u8_APBx_DIVIDED_BY_16					0b111

/*******************************************************************************
*                        		AHB Prescaler		                           *
*******************************************************************************/
#define RCC_u8_AHB_DIVIDED_BY_1						0b0000
#define RCC_u8_AHB_DIVIDED_BY_2						0b1000
#define RCC_u8_AHB_DIVIDED_BY_4						0b1001
#define RCC_u8_AHB_DIVIDED_BY_8						0b1010
#define RCC_u8_AHB_DIVIDED_BY_16					0b1011
#define RCC_u8_AHB_DIVIDED_BY_64					0b1100
#define RCC_u8_AHB_DIVIDED_BY_128					0b1101
#define RCC_u8_AHB_DIVIDED_BY_256					0b1110
#define RCC_u8_AHB_DIVIDED_BY_512					0b1111

/*******************************************************************************
*                           Static Configurations                              *
*******************************************************************************/
/*******************************************************************************
*                      Configure the system clock
*                      1- RCC_u8_HSI
*                      2- RCC_u8_HSE
*                      3- RCC_u8_PLL
*******************************************************************************/
#define RCC_u8_CLK_SYS			RCC_u8_HSE

/*******************************************************************************
*                      Configure the PLL clock source
*                       1- RCC_u8_PLL_HSI_DIVIDED_BY_2
*                       2- RCC_u8_PLL_HSE
*                       3- RCC_u8_PLL_HSE_DIVIDED_BY_2
*
*                      Configure the HSE clock source
*                       1-  RCC_u8_PLL_MULTIPLY_BY_2
*                       2-  RCC_u8_PLL_MULTIPLY_BY_3
*                       3-  RCC_u8_PLL_MULTIPLY_BY_4
*						4-  RCC_u8_PLL_MULTIPLY_BY_5
*						5-  RCC_u8_PLL_MULTIPLY_BY_6
*						6-  RCC_u8_PLL_MULTIPLY_BY_7
*						7-  RCC_u8_PLL_MULTIPLY_BY_8
*						8-  RCC_u8_PLL_MULTIPLY_BY_9
*						9-  RCC_u8_PLL_MULTIPLY_BY_10
*						10- RCC_u8_PLL_MULTIPLY_BY_11
*						11- RCC_u8_PLL_MULTIPLY_BY_12
*						12- RCC_u8_PLL_MULTIPLY_BY_13
*						13- RCC_u8_PLL_MULTIPLY_BY_14
*						14- RCC_u8_PLL_MULTIPLY_BY_15
*						15- RCC_u8_PLL_MULTIPLY_BY_16
*******************************************************************************/
#if (RCC_u8_CLK_SYS == RCC_u8_PLL)
	#define RCC_u8_PLL_SOURCE			RCC_u8_PLL_HSI_DIVIDED_BY_2
	#define RCC_u8_PLL_MULTIPLIER		RCC_u8_PLL_MULTIPLY_BY_2
#endif

/*******************************************************************************
*                      Configure the HSE clock source
*                       1- RCC_u8_HSE_NOT_BYPASS
*                       2- RCC_u8_HSE_BYPASS
*******************************************************************************/
#if (RCC_u8_CLK_SYS == RCC_u8_HSE)
	#define RCC_u8_HSE_TYPE			RCC_u8_HSE_NOT_BYPASS
#endif

/*******************************************************************************
*                      The Trim Value of HSI
*                      Any value between 0~31
*                      Default = 16
*******************************************************************************/
#define RCC_u8_HSI_TRIM				16

/*******************************************************************************
*                      Configure the prescaler for the ADC
*                       1- RCC_u8_ADC_DIVIDED_BY_2
*						2- RCC_u8_ADC_DIVIDED_BY_4
*						3- RCC_u8_ADC_DIVIDED_BY_6
*						4- RCC_u8_ADC_DIVIDED_BY_8
*******************************************************************************/
#define RCC_u8_ADC_PRESCALER				RCC_u8_ADC_DIVIDED_BY_2

/*******************************************************************************
*                      Configure the prescaler for the APBx bus
*                       1- RCC_u8_APBx_DIVIDED_BY_1
*						2- RCC_u8_APBx_DIVIDED_BY_2
*						3- RCC_u8_APBx_DIVIDED_BY_4
*						4- RCC_u8_APBx_DIVIDED_BY_8
*						5- RCC_u8_APBx_DIVIDED_BY_16
*
*                      Configure the prescaler for the AHB bus
*                       1- RCC_u8_AHB_DIVIDED_BY_1
*						2- RCC_u8_AHB_DIVIDED_BY_2
*						3- RCC_u8_AHB_DIVIDED_BY_4
*						4- RCC_u8_AHB_DIVIDED_BY_8
*						5- RCC_u8_AHB_DIVIDED_BY_16
*						6- RCC_u8_AHB_DIVIDED_BY_64
*						7- RCC_u8_AHB_DIVIDED_BY_128
*						8- RCC_u8_AHB_DIVIDED_BY_256
*						8- RCC_u8_AHB_DIVIDED_BY_512
*******************************************************************************/
#define RCC_u8_APB1_PRESCALER				RCC_u8_APBx_DIVIDED_BY_1
#define RCC_u8_APB2_PRESCALER				RCC_u8_APBx_DIVIDED_BY_1
#define RCC_u8_AHB_PRESCALER				RCC_u8_AHB_DIVIDED_BY_1

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
/*******************************************************************************
* Function Name:        rcc_init_system_clock
* Description:          Function to init the system clock source
* Parameters (in):      void
* Parameters (out):     u8
* Return value:         SUCCESS or ERROR
********************************************************************************/
s32 rcc_init_system_clock(void)
{
	s32 s32_return = SUCCESS;
	u32 u32_timeout = 0;

	RCC->CR = (RCC->CR &~ (0b11111<<3)) | (RCC_u8_HSI_TRIM << 3); /* Setting the TRIM value for HSI */
    
    do
    {
        #if (RCC_u8_CLK_SYS == RCC_u8_HSI)
            SET_BIT(RCC->CR, 0); /* write one bit no0 HSION to enable it*/
            /* wait until HSI RDY flag = 1 or timeout occurs*/
            while((GET_BIT(RCC->CR,1) == 0) && (u32_timeout < MAX_TIMEOUT))
            {
                u32_timeout++;
            }
        
            if(u32_timeout > MAX_TIMEOUT)
            {
                s32_return = ERROR_TIMEOUT;
                break;
            }
            CLR_BIT(RCC->CFGR, 0); /* Select HSI as clock source from SW registers */
            CLR_BIT(RCC->CFGR, 1);

        #elif (RCC_u8_CLK_SYS == RCC_u8_HSE)
            #if (RCC_u8_HSE_TYPE == RCC_u8_HSE_BYPASS)
                SET_BIT(RCC->CR, 18);
            #elif (RCC_u8_HSE_TYPE == RCC_u8_HSE_NOT_BYPASS)
                CLR_BIT(RCC->CR, 18);
            #else
                #error "Wrong System Clock Choice"
            #endif
            
            SET_BIT(RCC->CR, 16); /* write one bit no16 HSEON */

            /* wait until HSE RDY flag = 1  or timeout occurs */
            while((GET_BIT(RCC->CR, 17) == 0) && (u32_timeout < MAX_TIMEOUT))
            {
                u32_timeout++;
            }
            
            if(u32_timeout > MAX_TIMEOUT)
            {
                s32_return = ERROR_TIMEOUT;
                break;
            }
            SET_BIT(RCC->CFGR,0); /* select HSE as system clock in SW registers */
            CLR_BIT(RCC->CFGR,1);

        #elif (RCC_u8_CLK_SYS == RCC_u8_PLL)
            /* Starting of First Nested If */
            #if ((RCC_u8_PLL_MULTIPLIER >= RCC_u8_PLL_MULTIPLY_BY_2) && (RCC_u8_PLL_MULTIPLIER <= RCC_u8_PLL_MULTIPLY_BY_16))
                RCC->CFGR = (RCC->CFGR &~ (0b1111 << 18)) | (RCC_u8_PLL_MULTIPLIER << 18) ;
            #else
                #warning "Wrong Multiplication Factor"
            #endif
            /* End of First Nested If */

            /* Starting of First Nested If */
            #if (RCC_u8_PLL_SOURCE == RCC_u8_PLL_HSI_DIVIDED_BY_2)
                CLR_BIT(RCC->CFGR, 16);
            #elif (RCC_u8_PLL_SOURCE == RCC_u8_PLL_HSE)
                SET_BIT(RCC->CR, 16); /* Enable the HSE first */
                SET_BIT(RCC->CFGR, 16);
                CLR_BIT(RCC->CFGR, 17);
            #elif (RCC_u8_PLL_SOURCE == RCC_u8_PLL_HSE_DIVIDED_BY_2)
                SET_BIT(RCC->CR, 16); /* Enable the HSE first */
                SET_BIT(RCC->CFGR, 16);
                SET_BIT(RCC->CFGR, 17);
            #else
                #error "Wrong System Clock Choice"
            #endif
            /* End of First Nested If */

            SET_BIT(RCC->CR, 24); /* write one bit no24 PLLON */
            /* wait until PLL RDY flag = 1 */
            while((GET_BIT(RCC->CR, 25) == 0) && (u32_timeout < MAX_TIMEOUT))
            {
                u32_timeout++;
            }
            
            if(u32_timeout > MAX_TIMEOUT)
            {
                s32_return = ERROR_TIMEOUT;
                break;
            }
            SET_BIT(RCC->CFGR, 1); /* select PLL as system clock in SW registers */
            CLR_BIT(RCC->CFGR, 0);
        #else
            #error"Wrong System Clock Choice"
        #endif

        /* Setting the Prescaler */
        RCC->CFGR = (RCC->CFGR &~ (0b11 << 14))  | (RCC_u8_ADC_PRESCALER << 14);  /* ADC */
        RCC->CFGR = (RCC->CFGR &~ (0b111 << 11)) | (RCC_u8_APB2_PRESCALER << 11); /* APB2 */
        RCC->CFGR = (RCC->CFGR &~ (0b111 << 8))  | (RCC_u8_APB1_PRESCALER << 8);  /* APB1 */
        RCC->CFGR = (RCC->CFGR &~ (0b1111 << 4)) | (RCC_u8_AHB_PRESCALER << 4);   /* AHB */
    }while(0);
    
	return s32_return;
}

/*******************************************************************************
* Function Name:        rcc_enable_disable_peripheral
* Description:          Function to enable or disable clock for specific periphral
* Parameters (in):      The required peripheral and its bus
* Parameters (out):     s32
* Return value:         SUCCESS or ERROR
********************************************************************************/
s32 rcc_enable_disable_peripheral(u8 u8_peripheral, bool b_state)
{
	s32 s32_return = SUCCESS;
    
    if((u8_peripheral < RCC_INVALID_PERIPHERAL) && (b_state <= TRUE))
    {
        if(u8_peripheral < RCC_APB2_OFFSET) /* from 0 to 31 AHB BUS */
        {
            WRITE_BIT(RCC->AHBENR, u8_peripheral, b_state);
        }
        else if(u8_peripheral < RCC_APB1_OFFSET) /* from 32 to 63 APB2 BUS */
        {
            u8_peripheral -= RCC_APB2_OFFSET;
            WRITE_BIT(RCC->APB2ENR, u8_peripheral, b_state);
        }
        else /* from 64 to 95 APB1 BUS */
        {
            u8_peripheral -= RCC_APB1_OFFSET;
            WRITE_BIT(RCC->APB1ENR, u8_peripheral, b_state);
        }
    }
    else
    {
        s32_return = ERROR_INVALID_ARGUMENTS; /* user entered wrong peripheral number */
    }
    
	return s32_return;
}
