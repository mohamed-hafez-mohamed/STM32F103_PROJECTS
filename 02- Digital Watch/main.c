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
#include <stdlib.h>
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "TFT_interface.h"
#include "DWATCH_interface.h"


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
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL);
	MRCC_voidEnableClock(RCC_APB2 , SPI1_PERIPHERAL);
	MGPIO_voidSetPinMode(PINA0, GPIO_OUTPUT_2M_PULL_UP_DN);
	MGPIO_voidSetPinMode(PINA2, GPIO_OUTPUT_2M_PULL_UP_DN);
	MSTK_voidInit();
	MSPI_voidInit();
	HTFT_voidInit();
	MSTK_voidSetIntervalPeriodic_ms(10, &ADWATCH_voidCalCulateTime, NULL);
  while(1)
  {
		ADWATCH_voidDisplayDay();
		ADWATCH_voidDisplay();
		//HTFT_u8DrawChar(10,20,'A',TFT_YELLOW_COLOR,TFT_WHITE_COLOR,1);
  }

}

/*************** END OF FUNCTIONS ***************************************************************************/
