/****************************************************************************
* Title                 :   BL   
* Filename              :   BL_private.h
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
/** @file  BL_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef BL_PRIVATE_H_
#define BL_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Auxaliary constants.
#define ONE_BYTE_TO_DIGIT               2
#define HALF_BYTE                        4
#define One_BYTE                        8
#define ONE_HALF_BYTE                   12   
#define CLEAR_LOW_PART                  0xFFFF0000
#define NUMBER_OF_DATA_BYTES_IN_RECORD  16    
#define FIRST_CHAR_COUNT_DIGIT          1
#define SECOND_CHAR_COUNT_DIGIT         2
#define FIRST_ADDRESS_DIGIT             3  
#define SECOND_ADDRESS_DIGIT            4  
#define THIRD_ADDRESS_DIGIT             5
#define FOURTH_ADDRESS_DIGIT            6
#define FIRST_DATA_DIGIT                9  
#define SECOND_DATA_DIGIT               10  
#define THIRD_DATA_DIGIT                11 
#define FOURTH_DATA_DIGIT               12
#define SCB_VTOR_ADDRESS                0xE000ED08
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
