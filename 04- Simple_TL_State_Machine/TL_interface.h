/****************************************************************************
* Title                 :   TL   
* Filename              :   TL_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   30/01/2021
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
*  30/01/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  TL_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef TL_INTERFACE_H_
#define TL_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum
{
   STATE_1 = 0,
   STATE_2,
   STATE_3,
   STATE_4
}TLStates_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TL_voidInitializeTrafficLineStack(void);
void TL_voidRunState1(void * Copy_voidPointer);
void TL_voidRunState2(void * Copy_voidPointer);
void TL_voidRunState3(void * Copy_voidPointer);
void TL_voidRunState4(void * Copy_voidPointer);
void TL_voidRunTlSystem(void);

#endif /*File_H_*/

/*** End of File **************************************************************/
