/*******************************************************************************
* Title                 :   main  
* Filename              :   main.c
* Author                :   Mohamed Hafez
* Origin Date           :   04/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file main.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/		
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "TL_interface.h"
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
* Function Definitions
*******************************************************************************/

int main()
{
    /* Initialize the RCC to HSE */
	  MRCC_voidInitSysClock();
	  MRCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL);
	  MGPIO_voidSetPinMode(PINA0, GPIO_OUTPUT_2M_PULL_UP_DN);
    MGPIO_voidSetPinMode(PINA1, GPIO_OUTPUT_2M_PULL_UP_DN);
    MGPIO_voidSetPinMode(PINA2, GPIO_OUTPUT_2M_PULL_UP_DN);
    MSTK_voidInit();
	  TL_voidInitializeTrafficLineStack();
    while(1)
    {
	  	 TL_voidRunTlSystem();
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/
