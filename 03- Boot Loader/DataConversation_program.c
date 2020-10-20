/*******************************************************************************
* Title                 :   DataConversion 
* Filename              :   DataConversion_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   22/09/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  22/09/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file DataConversion_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DataConversation_interface.h"
#include "DataConversation_config.h"
#include "DataConversation_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
u8 LDataConv_u8AsciiToHex(u8 Copy_u8Asci)
{
	u8 Local_u8Result;
	if ( (Copy_u8Asci >= ZERO_IN_ASCII) && (Copy_u8Asci <= NINE_IN_ASCII) )
	{
		Local_u8Result = Copy_u8Asci - CONVERT_NUMBERS_UNDER_NINE_ASCII_TO_HEX;
	}

	else
	{
		Local_u8Result = Copy_u8Asci - CONVERT_NUMBERS_ABOVE_NINE_TO_HEX;
	}

	return Local_u8Result;
}


/*************** END OF FUNCTIONS ***************************************************************************/
