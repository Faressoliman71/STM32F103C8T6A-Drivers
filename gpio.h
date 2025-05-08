/*******************************************
* 
* Date : 28 april 2025
* 
********************************************/


/****************************INCLUDES*************/
#ifndef GPIO_H
#define GPIO_H
#include "common.h"

/************************************************/
typedef enum
{
	PINA0  ,
	PINA1 ,
	PINA2 ,
	PINA3 ,
	PINA4 ,
	PINA5 ,
	PINA6 ,
	PINA7 ,
	PINA8 ,
	PINA9 ,
	PINA10 ,
	PINA11 ,
	PINA12 ,
	PINA13 ,
	PINA14 ,
	PINA15  ,
	PINB0 ,
	PINB1 ,
	PINB2 ,// not availabe ( Hardwired to GND BOOT1 )
	PINB3 ,
	PINB4 ,
	PINB5 ,
	PINB6 ,
	PINB7 ,
	PINB8 ,
	PINB9 ,
	PINB10 ,
	PINB11 ,
	PINB12 ,
	PINB13 ,
	PINB14 ,
	PINB15 ,	
    PINC13 ,
    PINC14 ,
    PINC15 ,
    INVALID_PIN	
	
}enu_pin_type;

typedef enum
{
    INPUT_FLOATING ,
	INPUT_PULL_UP ,
	INPUT_PULL_DOWN ,
	INPUT_ANALOG ,
	OUTPUT_OPEN_DRAIN ,
	OUTPUT_PUSH_PULL ,
	AF_PUSH_PULL ,
	AF_OPEN_DRAIN ,
    INVALID_STATUS	
}enu_status_type;



typedef enum 
{
	INPUT_MODE ,
	OUTPUT_MODE_10_MHZ ,
	OUTPUT_MODE_2_MHZ,
	OUTPUT_MODE_50_MHZ,
    INVALID_MODE
	
}enu_mode_type;

typedef enum 
{
	PORTA ,
	PORTB ,
	PORTC ,
    INVALID_PORT_TYPE
	
}enu_port_type;


typedef enum 
{
   LOGIC_LOW,
   LOGIC_HIGH,
   INVALID_LOGIC    
    
}enu_pin_logic;


/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/




/*******************************************************************************
* Function Name:        gpio_init_pin
* Description:          Function to init pin
* Parameters (in):     PIN_TYPE pin , PIN_STATUS status
* Parameters (out):     s32
* Return value:         SUCCESS or ERROR
********************************************************************************/
s32 gpio_init_pin (enu_pin_type pin ,enu_mode_type mode, enu_status_type status);

/*******************************************************************************
* Function Name:        gpio_write_pin
* Description:          Function to init pin
* Parameters (in):     PIN_TYPE pin , u8 u8_data
* Parameters (out):     s32
* Return value:         SUCCESS or ERROR
********************************************************************************/
s32 gpio_write_pin ( enu_pin_type pin , enu_pin_logic enu_pin_logic_state);




    
/*******************************************************************************
* Function Name:        gpio_read_pin
* Description:          Function to read pin
* Parameters (in):     enu_port_type pin , enu_pin_logic * logic
* Parameters (out):     s32
* Return value:         SUCCESS or ERROR
********************************************************************************/	
	
	
 s32 gpio_read_pin ( enu_pin_type pin , enu_pin_logic * penu_pin_logic_state);
 
 /*******************************************************************************
* Function Name:		gpio_deinit_pin
* Description:			Function to deinit the mode for the required pin mode
* Parameters (in):    	The required pin number 
* Parameters (out):   	s32
* Return value:      	OK or Error
********************************************************************************/
s32 gpio_deinit_pin (enu_pin_type enu_pin);
 
 
 #endif
 