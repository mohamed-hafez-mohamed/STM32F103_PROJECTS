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
#include "FPEC_interface.h"
#include "DataConversation_interface.h"
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
static u32 Static_u32RecordAddress;
static u16 Static_u16DataRecord[NUMBER_OF_DATA_BYTES_IN_RECORD + 1];
Function_t AddressToCall;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : ABL_voidParseData()
*//** 
* \b Description:
*
* This function is used to parse the record in hex file. 
*
* PRE-CONDITION:  Record digits stored in a buffer.
* 
* POST-CONDITION: None
*
* @param [in]     The address of the buffer tha contain record digits.
* 
* @return 		   Void.
*
* \b Example Example:
* @code
* 	ABL_voidParseData(&Record);
*
* @endcode
*
* @see ABL_voidParseData
*
*******************************************************************************/
void ABL_voidParseData(u8 * Copy_u8BufferRecord)
{
   // Initialize data record buffer.
   for(u8 Local_u8Counter = 0;Local_u8Counter < NUMBER_OF_DATA_BYTES_IN_RECORD;Local_u8Counter++)
   {
      Static_u16DataRecord[Local_u8Counter] = 0;
   }
   u8 Local_u8HighDigit, Local_u8LowDigit, Local_u8CharCount;
   u8 Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3;
   u8 Local_u8DataCounter = 0;
   // Get character count from the record.
   // CC is one byte.
   // Each digit represents half byte
   // so we shif left high digit 4 bits.
   Local_u8HighDigit  = Copy_u8BufferRecord[FIRST_CHAR_COUNT_DIGIT];
   Local_u8LowDigit   = Copy_u8BufferRecord[SECOND_CHAR_COUNT_DIGIT];
   Local_u8CharCount  = ((Local_u8HighDigit << HALF_BYTE) | Local_u8LowDigit);
   // Get the physical address of the record.
   // Address is two bytes.
   Local_u8Digit0     = Copy_u8BufferRecord[FIRST_ADDRESS_DIGIT ];
   Local_u8Digit1     = Copy_u8BufferRecord[SECOND_ADDRESS_DIGIT];
   Local_u8Digit2     = Copy_u8BufferRecord[THIRD_ADDRESS_DIGIT];
   Local_u8Digit3     = Copy_u8BufferRecord[FOURTH_ADDRESS_DIGIT];
   // Clear the low part of address.
   Static_u32RecordAddress = HIGH_PART_OF_ADDRESS & CLEAR_LOW_PART;
   // Set the address of the first byte in the record.
   Static_u32RecordAddress = ((HIGH_PART_OF_ADDRESS) | (Local_u8Digit0 << ONE_HALF_BYTE) | (Local_u8Digit1 << One_BYTE)
                            | (Local_u8Digit2 << HALF_BYTE) | (Local_u8Digit3));

   // Get half word of data to write it on the flash
   // and this because the flash driver can write half word only.
   for(u8 Local_u8BytesCounter = 0;Local_u8BytesCounter < (Local_u8CharCount / ONE_BYTE_TO_DIGIT);Local_u8BytesCounter++)
   {
      Local_u8Digit0  = LDataConv_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + FIRST_DATA_DIGIT]);
      Local_u8Digit1  = LDataConv_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + SECOND_DATA_DIGIT]);
      Local_u8Digit2  = LDataConv_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + THIRD_DATA_DIGIT]);
      Local_u8Digit3  = LDataConv_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + FOURTH_DATA_DIGIT]);
      Static_u16DataRecord[Local_u8DataCounter] = ((Local_u8Digit2  << ONE_HALF_BYTE) | (Local_u8Digit3 << One_BYTE)
                                                  | (Local_u8Digit0 << HALF_BYTE)     | (Local_u8Digit1));
      Local_u8DataCounter++;
   }
   // Write the data in the record on the flash.
   MFPEC_u8ProgramFlash(Static_u32RecordAddress, Static_u16DataRecord, Local_u8CharCount / ONE_BYTE_TO_DIGIT);
}

/******************************************************************************
* Function : ABL_voidJumpToApp()
*//** 
* \b Description:
*
* This function is used to jump to app if there is no update. 
*
* PRE-CONDITION:  No write to flash request.
* 
* POST-CONDITION: None
*
* @param [in]     void.
* 
* @return 		   Void.
*
* \b Example Example:
* @code
* 	ABL_voidJumpToApp();
*
* @endcode
*
* @see ABL_voidJumpToApp
*
*******************************************************************************/
void ABL_voidJumpToApp(void)
{
   #define SCB_VTOR   *((volatile u32 * const)SCB_VTOR_ADDRESS)
   // Setting the offset of the vector table.
	SCB_VTOR = ADRESS_OF_APP_STARTUP;
   AddressToCall = *(Function_t*)(ADRESS_OF_APP);
   // Jump to app based on the address
   AddressToCall();
}
/*************** END OF FUNCTIONS ***************************************************************************/
