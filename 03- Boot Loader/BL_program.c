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
static u32 Static_u32BaseAddress = 0x08000000;
static u32 Static_u32RecordAddress;
static u16 Static_u16DataRecord[NUMBER_OF_DATA_BYTES_IN_RECORD + ADD_NULL_CHARACTER_PLACE ];
Function_t AddressToCall = 0;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static u8 ABL_u8AsciiToHex(u8 Copy_u8Ascii)
{
	u8 Local_u8Result;
	if ( (Copy_u8Ascii >= ZERO_IN_ASCII) && (Copy_u8Ascii <= NINE_IN_ASCII) )
	{
		Local_u8Result = Copy_u8Ascii - CONVERT_NUMBERS_UNDER_NINE_ASCII_TO_HEX;
	}
	else
	{
		Local_u8Result = Copy_u8Ascii - CONVERT_NUMBERS_ABOVE_NINE_TO_HEX;
	}
	return Local_u8Result;
}
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
   for(u8 Local_u8Counter = 0;Local_u8Counter < NUMBER_OF_DATA_BYTES_IN_RECORD + 3;Local_u8Counter++)
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
   Local_u8HighDigit  = ABL_u8AsciiToHex(Copy_u8BufferRecord[FIRST_CHAR_COUNT_DIGIT]);
   Local_u8LowDigit   = ABL_u8AsciiToHex(Copy_u8BufferRecord[SECOND_CHAR_COUNT_DIGIT]);
   Local_u8CharCount  = ((Local_u8HighDigit << HALF_BYTE) | Local_u8LowDigit);
   // Get the physical address of the record.
   // Address is two bytes.
   Local_u8Digit0     = ABL_u8AsciiToHex(Copy_u8BufferRecord[FIRST_ADDRESS_DIGIT]);
   Local_u8Digit1     = ABL_u8AsciiToHex(Copy_u8BufferRecord[SECOND_ADDRESS_DIGIT]);
   Local_u8Digit2     = ABL_u8AsciiToHex(Copy_u8BufferRecord[THIRD_ADDRESS_DIGIT]);
   Local_u8Digit3     = ABL_u8AsciiToHex(Copy_u8BufferRecord[FOURTH_ADDRESS_DIGIT]);
   // Set the address of the first byte in the record.
   Static_u32RecordAddress = ((Local_u8Digit3 << ONE_HALF_BYTE) | (Local_u8Digit2 << ONE_BYTE) |
                             (Local_u8Digit1 << HALF_BYTE)     | (Local_u8Digit0));
   Static_u32RecordAddress = (HIGH_PART_OF_ADDRESS) | (Static_u32RecordAddress);                       
   // Get half word of data to write it on the flash
   // and this because the flash driver can write half word only.
   for(u8 Local_u8BytesCounter = 0;Local_u8BytesCounter < (Local_u8CharCount / ONE_BYTE_TO_DIGIT);Local_u8BytesCounter++)
   {
      Local_u8Digit0  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + FIRST_DATA_DIGIT]);
      Local_u8Digit1  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + SECOND_DATA_DIGIT]);
      Local_u8Digit2  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + THIRD_DATA_DIGIT]);
      Local_u8Digit3  = ABL_u8AsciiToHex(Copy_u8BufferRecord[(HALF_BYTE * Local_u8BytesCounter) + FOURTH_DATA_DIGIT]);
      Static_u16DataRecord[Local_u8DataCounter] = ((Local_u8Digit2  << ONE_HALF_BYTE) | (Local_u8Digit3 << ONE_BYTE)
                                                  | (Local_u8Digit0 << HALF_BYTE)     | (Local_u8Digit1));
      Local_u8DataCounter++;
   }
   // Write the data in the record on the flash.
   MFPEC_u8ProgramFlash(Static_u32RecordAddress, Static_u16DataRecord, (Local_u8CharCount / ONE_BYTE_TO_DIGIT));
}

void ABL_voidParseUPperAddress(u8 * Copy_u8BufferRecord)
{
   u8  Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3;
   u32 Local_u32Address;
   Local_u8Digit0        = ABL_u8AsciiToHex(Copy_u8BufferRecord[FOURTH_DATA_DIGIT]);
   Local_u8Digit1        = ABL_u8AsciiToHex(Copy_u8BufferRecord[THIRD_DATA_DIGIT]);
   Local_u8Digit2        = ABL_u8AsciiToHex(Copy_u8BufferRecord[SECOND_DATA_DIGIT]);
   Local_u8Digit3        = ABL_u8AsciiToHex(Copy_u8BufferRecord[FIRST_DATA_DIGIT]);
   Local_u32Address      = ((Local_u8Digit3   << ONE_HALF_BYTE) | (Local_u8Digit2 << ONE_BYTE) |
                           (Local_u8Digit1    << HALF_BYTE)     | (Local_u8Digit0));
   Static_u32BaseAddress = (Local_u32Address  << TWO_BYTE);
}

void ABL_voidParseRecord(u8 * Copy_u8BufferRecord)
{
   switch (Copy_u8BufferRecord[8])
	{
	   case '0': ABL_voidParseData(Copy_u8BufferRecord);         break;
	   case '4': ABL_voidParseUPperAddress(Copy_u8BufferRecord); break;
	}
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
   #define SCB_VTOR   *((volatile u32 *)SCB_VTOR_ADDRESS)
   // Setting the offset of the vector table.
	SCB_VTOR = ADRESS_OF_APP_STARTUP;
   AddressToCall = *(Function_t*)(ADRESS_OF_APP);
   // Jump to app based on the address
   AddressToCall();
}


/*************** END OF FUNCTIONS ***************************************************************************/
