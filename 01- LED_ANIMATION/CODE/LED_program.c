/*******************************************************************************
* Title                 :   LED 
* Filename              :   LED_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   17/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  17/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file LED_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"

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


void LED_voidInit(GPIO_PinId_t copy_u8PinId)
{
	GPIO_voidSetPinMode(copy_u8PinId, LED_PIN_MODE);
}

void LED_voidSetLed(GPIO_PinId_t copy_u8PinId)
{
    
    GPIO_voidSetPinValue(copy_u8PinId, HIGH);
}

void LED_voidClrLed(GPIO_PinId_t copy_u8PinId)
{
    GPIO_voidSetPinValue(copy_u8PinId, LOW);
}

void LED_voidTogLed(GPIO_PinId_t copy_u8PinId)
{
    GPIO_voidSetPinValue(copy_u8PinId, HIGH);
    for(u16 i =0;i < 1000;i++)
		  {  
				for(u16 j =0;j < 1000;j++)
				{
				    __asm("NOP");
				}
		  }
    GPIO_voidSetPinValue(copy_u8PinId, LOW);
    for(u16 i =0;i < 1000;i++)
		  {  
				for(u16 j =0;j < 1000;j++)
				{
				    __asm("NOP");
				}
		  }
}

/*************** END OF FUNCTIONS ***************************************************************************/
