/*******************************************************************************
* Title                 :   BL 
* Filename              :   BL_program.c
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
/** @file BL_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "BL_interface.h"
#include "CRC_interface.h"
#include "GPIO_interface.h"
#include "FPEC_interface.h"
#include "UART_interface.h"
#include "UDS_interface.h"
#include "WDT_interface.h"
#include "BL_config.h"
#include "BL_private.h"

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
extern Global_u8FirstFlashingFlag;
/******************************************************************************
* Function Definitions
*******************************************************************************/
static u8 ABL_u8AsciiToHex(u8 Copy_u8Ascii)
{
   u8 Local_u8Result;
   if ((Copy_u8Ascii >= ZERO_IN_ASCII) && (Copy_u8Ascii <= NINE_IN_ASCII) )
   {
   	Local_u8Result = Copy_u8Ascii - CONVERT_NUMBERS_UNDER_NINE_ASCII_TO_HEX;
   }
   else
   {
   	Local_u8Result = Copy_u8Ascii - CONVERT_NUMBERS_ABOVE_NINE_TO_HEX;
   }
   return Local_u8Result;
}

void ABL_voidHandleActiveImageVectorTable(void)
{
	// Setting the offset of the vector table.
   SCB_VTOR = ADRESS_OF_ACTIVE_IMAGE_STARTUP;
}

void ABL_voidStoreRecord(u8 * Copy_u8BufferRecord, u32 Copy_u32RecordAdddress)
{
  // Initialize Local Variables.
  u8 Local_u8DataCounter                                      = BL_INITIALIZE_WITH_ZERO;
  u8 Local_u8Digit0                                           = BL_INITIALIZE_WITH_ZERO;
  u8 Local_u8Digit1                                           = BL_INITIALIZE_WITH_ZERO;
  u8 Local_u8Digit2                                           = BL_INITIALIZE_WITH_ZERO;
  u8 Local_u8Digit3                                           = BL_INITIALIZE_WITH_ZERO; 
  u16 Local_u16DataRecord[NUMBER_OF_DATA_HALF_WORD_IN_RECORD] = {BL_INITIALIZE_WITH_ZERO};        
  // Get half word of data to write it on the flash
  // and this because the flash driver can write half word only.
   for(u8 Local_u8BytesCounter = 0;Local_u8BytesCounter < NUMBER_OF_DATA_HALF_WORD_IN_RECORD;Local_u8BytesCounter++)
   {
     Local_u8Digit0  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE_SIZE_IN_BITS * Local_u8BytesCounter) + FIRST_DATA_DIGIT]);
     Local_u8Digit1  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE_SIZE_IN_BITS * Local_u8BytesCounter) + SECOND_DATA_DIGIT]);
     Local_u8Digit2  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE_SIZE_IN_BITS * Local_u8BytesCounter) + THIRD_DATA_DIGIT]);
     Local_u8Digit3  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE_SIZE_IN_BITS * Local_u8BytesCounter) + FOURTH_DATA_DIGIT]);
     Local_u16DataRecord[Local_u8DataCounter] = ((Local_u8Digit2 << ONE_HALF_BYTE_SIZE_IN_BITS) | (Local_u8Digit3 << ONE_BYTE_SIZE_IN_BITS)
                                              |  (Local_u8Digit0 << HALF_BYTE_SIZE_IN_BITS)     | (Local_u8Digit1));
     Local_u8DataCounter++;
   }
   // Write the data in the record on the flash.
   MFPEC_u8ProgramFlash(Copy_u32RecordAdddress, Local_u16DataRecord, NUMBER_OF_DATA_HALF_WORD_IN_RECORD);
}

void ABL_voidReceiveCode(void)
{
    u8  Local_u8RecordBuffer[BL_NUMBER_OF_DIGITS_IN_RECORD]  = {BL_INITIALIZE_WITH_ZERO};
    u8  Local_u8RecordCounter                                = BL_RESET_COUNTER_TO_START_NEW_REC ;
    u8  Local_u8UartReceivedStatus                           = BLNOT_RECEIVED;
    u8  Local_u8GatewayRequest                               = BL_INITIALIZE_WITH_FALSE;
    u32 Local_u32InactiveImageAddressCounter                 = ADRESS_OF_ACTIVE_IMAGE_STARTUP;
    // Erasing flash only one time to be written.
    MFPEC_voidEraseAppArea(FIRST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION, LAST_PAGE_NUMBER_IN_ACTIVE_IMAGE_REGION);
    // Acknowledge Gateway that Header Received.
    MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_HEADER_RECEIVED);
    Local_u8GatewayRequest = MUART_u8ReceiveByteSynch();
    if(Local_u8GatewayRequest == UDS_GWY_REQUEST_SENDING_LINE_OF_CODE)
    {
	while(1)
        {
            // Store the UART status.
	    Local_u8UartReceivedStatus = MUART_u8ReceiveSynch(&(Local_u8RecordBuffer[Local_u8RecordCounter]));
            // Check the UART status received data or not.
            if(Local_u8UartReceivedStatus == BL_RECEIVED_DATA)
            {
                if(Local_u8RecordBuffer[Local_u8RecordCounter] == BL_THE_LAST_DIGIT_IN_RECORD)
                {
                    // Parse record contents and flash data.
                    ABL_voidStoreRecord(Local_u8RecordBuffer, Local_u32InactiveImageAddressCounter);
                    // Acknowledge code sender to send another record.
                    MUART_voidTransmitSynch(UDS_MCU_ACKNOWLEDGE_LINE_OF_CODE_RECEIVED);
                    Local_u8RecordCounter = BL_RESET_COUNTER_TO_START_NEW_REC;
	            // Deermine The Address Of the Next Record.
	            Local_u32InactiveImageAddressCounter += BL_INCREASE_RECORD_ADDRESS_WITH_16_BYTE;
                }
		else if(Local_u8RecordBuffer[Local_u8RecordCounter] == UDS_GWY_ACKNOWLEDGE_FINISHING)
		{
	            ABL_voidFinishBootLoader();
		}
                else
                {
                    Local_u8RecordCounter++;
                }
            }
            else
            {
                // Don't do anything.
            }
        }
   }
   else
   {
       // Don't do anything.
   }
}

void ABL_voidFinishBootLoader(void)
{
    // Acknowledge Gateway that the New Cod Received.
    MUART_voidTransmitByteSynch(UDS_MCU_ACKNOWLEDGE_FINISHING);
    // Update Headers
    FEE_voidEraseRestoreHeaderPage(ACTIVE_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_ACTIVE);
    FEE_voidEraseRestoreHeaderPage(BACKUP_IMAGE_STATUS_ADDRESS, BR_SET_IMAGE_BACKUP);
    // Move Vector table to the active region.
    ABL_voidHandleActiveImageVectorTable();
    // Move the active image to the backup region when the backup region erased.
    if(Global_u8FirstFlashingFlag == BL_FIRST_FLASHING)
    {
	__disable_irq();
    	Global_u8FirstFlashingFlag = BL_NOT_FIRST_FLASHING;
	__enable_irq();
    	ABR_voidCopyImageToBackupRegion();
    }
    // Reset Branching Flag.
    FEE_voidEraseRestoreHeaderPage(BL_BRANCHING_FLAG_ADDRESS, BL_RESET_BRANCHING_FLAG);
    // Make Software Reset.
    IWDT_voidMakeSoftWareReset();
}

/*************** END OF FUNCTIONS ***************************************************************************/
