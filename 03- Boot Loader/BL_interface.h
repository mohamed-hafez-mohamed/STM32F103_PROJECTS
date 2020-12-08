/****************************************************************************
* Title                 :   BL   
* Filename              :   BL_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   14/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  14/10/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  BL_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef BL_INTERFACE_H_
#define BL_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define NUMBER_OF_DIGITS_IN_RECORD        45
#define WAIT_TIME                         15000
#define RECEIVED_DATA                     1
#define THE_LAST_NUMBER_IN_RECORD         '\n'
#define WRITING_FLASH_REQUSTED            1
#define DISABLE_FLASH_REQUEST             0
#define RESET_COUNTER_TO_START_NEW_REC    0
/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void (*Function_t)(void);
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void ABL_voidParseData(u8 * Copy_u8BufferRecord);
void ABL_voidParseUPperAddress(u8 * Copy_u8BufferRecord);
void ABL_voidParseRecord(u8 * Copy_u8BufferRecord); 
void ABL_voidJumpToApp(void);
#endif /*File_H_*/

/*** End of File **************************************************************/
