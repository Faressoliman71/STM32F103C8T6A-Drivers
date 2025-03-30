/******************************************************************************
*  File name:		common.h
*  Date:			Mar 7, 2024
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef COMMON_H_
#define COMMON_H_
/*******************************************************************************
*                      Include                                                 *
*******************************************************************************/
#include "error_codes.h"
#include "std_types.h"

/*******************************************************************************
*                      Macros                                                  *
*******************************************************************************/
#define SET_BIT(VAR, BITNO)     		VAR |= (1 << BITNO)
#define CLR_BIT(VAR, BITNO)     		VAR &= ~(unsigned) (1 << BITNO)
#define GET_BIT(VAR, BITNO)     		((VAR >> BITNO) & 1)
#define TOG_BIT(VAR, BITNO)     		VAR ^= (1<<BITNO)
#define WRITE_BIT(VAR, BITNO, VALUE) 	VAR = (VAR & ~(1 << BITNO)) | ((VALUE & 1) << BITNO)

#endif

