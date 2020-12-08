/*******************************************************************************
* Title                 :   main  
* Filename              :   main.c
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  14/10/20   1.0.0   Mohamed Hafez   Initial Release.
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
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "BL_interface.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define FIRST_PAGE_NUMBER_IN_APP_AREA   8
#define LAST_PAGE_NUMBER_IN_APP_AREA    64
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static volatile u8  Static_u8RecordBuffer[NUMBER_OF_DIGITS_IN_RECORD];
static volatile u8  Static_u8RecordCounter;
static volatile u16 Static_u16TimerCounter;
static volatile u8  Static_u8BLWriteRequest;
static volatile u8  Static_u8TimeOutFlag;
/******************************************************************************
* Function Definitions
*******************************************************************************/
	
int main()
{
  // Set the variables values.
  Static_u8RecordCounter   = 0;
  Static_u16TimerCounter   = 0;
  Static_u8BLWriteRequest  = 1;
  Static_u8TimeOutFlag     = 0;
  u8 Local_u8RecordStatus  = 0;
  // Initialize peripheral used.
  MRCC_voidInitSysClock();
  MRCC_voidEnableClock(RCC_APB2, IOPA_PERIPHERAL);
  MRCC_voidEnableClock(RCC_APB2, USART1_PERIPHERAL);
  //MRCC_voidEnableClock(RCC_AHB , FLITF_PERIPHERAL);
  MSTK_voidInit();
  MUART_voidInit();
  MGPIO_voidSetPinMode(UART_1_TX,  AFIO_OUTPUT_2M_PULL_UP_DN);
  MGPIO_voidSetPinMode(UART_1_RX, GPIO_INPUT_FLOATING);
  MSTK_voidSetIntervalSingle_ms(WAIT_TIME, &ABL_voidJumpToApp, NULL);
  while(1)
  {
    // Store the UART status.
	  Local_u8RecordStatus = MUART_u8ReceiveSynch(&(Static_u8RecordBuffer[Static_u8RecordCounter]));
    // Check the UART status received data or not.
    if(Local_u8RecordStatus == RECEIVED_DATA)
    {
      MSTK_voidStopStk();
      if(Static_u8RecordBuffer[Static_u8RecordCounter] == THE_LAST_NUMBER_IN_RECORD)
      {
        if(Static_u8BLWriteRequest == WRITING_FLASH_REQUSTED)
        {
          // Erasing flash only one time to be writed.
          MFPEC_voidEraseAppArea(FIRST_PAGE_NUMBER_IN_APP_AREA, LAST_PAGE_NUMBER_IN_APP_AREA);
          Static_u8BLWriteRequest = DISABLE_FLASH_REQUEST;
        }
        // Parse record contents and flash data.
        ABL_voidParseRecord(Static_u8RecordBuffer);
        // Acknowlage code sender to send anothe record.
        MUART_voidTransmitSynch("ok");
        Static_u8RecordCounter = RESET_COUNTER_TO_START_NEW_REC;
      }
      else
      {
        Static_u8RecordCounter++;
      }
      MSTK_voidSetIntervalSingle_ms(WAIT_TIME, ABL_voidJumpToApp, NULL);
    }
    else
    {
      // Don't do anything.
    }
  }
}

/*************** END OF FUNCTIONS ***************************************************************************/
