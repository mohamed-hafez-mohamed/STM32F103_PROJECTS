/*******************************************************************************
* Title                 :   APP 
* Filename              :   APP_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   10/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  25/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file APP_program.c
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
#include "LED_interface.h"
#include "APP_interface.h"
#include "APP_config.h"
#include "APP_private.h"

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

void APP_voidInit(void)
{
	
  /* Initialize the RCC to HSE */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL);
	GPIO_voidSetPortMode(PINA0, PINA7, GPIO_OUTPUT_2M_PULL_UP_DN);
	MSTK_voidInit();
}

void App_voidPingPong(void)
{
	u8 Local_u8Counter1;
  u8 Local_u8Counter2;
	for(Local_u8Counter1 = 0;Local_u8Counter1 < 4;Local_u8Counter1++)
	{
	  for(Local_u8Counter2 = 0;Local_u8Counter2 < 8;Local_u8Counter2++)
	  {
	    LED_voidSetLed(Local_u8Counter2);
		  MSTK_voidSetBusyWait_ms(200);
		  LED_voidClrLed(Local_u8Counter2);
		  MSTK_voidSetBusyWait_ms(200);
	  }
		for(Local_u8Counter2 = 6;Local_u8Counter2 > 0;Local_u8Counter2--)
	  {
	    LED_voidSetLed(Local_u8Counter2);
		  MSTK_voidSetBusyWait_ms(200);
		  LED_voidClrLed(Local_u8Counter2);
		  MSTK_voidSetBusyWait_ms(200);
	  }
	}
}

void App_voidInOut(void)
{
  u8 Local_u8Counter1;
  u8 Local_u8Counter2;
	
	  LED_voidSetLed(3);
		LED_voidSetLed(4);
		MSTK_voidSetBusyWait_ms(200);
		LED_voidClrLed(3);
	  LED_voidClrLed(4);
		MSTK_voidSetBusyWait_ms(200);
	for(Local_u8Counter1 = 0;Local_u8Counter1 < 4;Local_u8Counter1++)
	{
		u8 Local_u8LeftPin1  = 2;
	  u8 Local_u8RightPin1 = 5;
		u8 Local_u8LeftPin2  = 1;
	  u8 Local_u8RightPin2 = 6;
	  for(Local_u8Counter2 = 0;Local_u8Counter2 < 4;Local_u8Counter2++)
	  {
	    LED_voidSetLed(Local_u8LeftPin1);
			LED_voidSetLed(Local_u8RightPin1);
		  MSTK_voidSetBusyWait_ms(200);
		  LED_voidClrLed(Local_u8LeftPin1);
			LED_voidClrLed(Local_u8RightPin1);
		  MSTK_voidSetBusyWait_ms(200);
			Local_u8LeftPin1--;
			Local_u8RightPin1++;
	  }
		for(Local_u8Counter2 = 0;Local_u8Counter2 < 3;Local_u8Counter2++)
	  {
	    LED_voidSetLed(Local_u8LeftPin2);
			LED_voidSetLed(Local_u8RightPin2);
		  MSTK_voidSetBusyWait_ms(200);
		  LED_voidClrLed(Local_u8LeftPin2);
			LED_voidClrLed(Local_u8RightPin2);
		  MSTK_voidSetBusyWait_ms(200);
			Local_u8LeftPin2++;
			Local_u8RightPin2--;
	  }
	}
}

void App_voidFlashing(void)
{
  u8 Local_u8Counter1;
  u8 Local_u8Counter2;
	for(Local_u8Counter1 = 0;Local_u8Counter1 < 8;Local_u8Counter1++)
	{
	  for(Local_u8Counter2 = 0;Local_u8Counter2 < 8;Local_u8Counter2++)
	  {
	    LED_voidSetLed(Local_u8Counter2);
	  }
		MSTK_voidSetBusyWait_ms(500);
		for(Local_u8Counter2 = 0;Local_u8Counter2 < 8;Local_u8Counter2++)
	  {
		  LED_voidClrLed(Local_u8Counter2);
	  }
		MSTK_voidSetBusyWait_ms(500);
	}
}

void App_voidLedAnimation(void)
{
  App_voidPingPong();
	App_voidInOut();
	App_voidFlashing();
}

/*************** END OF FUNCTIONS ***************************************************************************/
