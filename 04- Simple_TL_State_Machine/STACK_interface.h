/****************************************************************************
* Title                 :   STACK
* Filename              :   STACK_interface.h
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
/** @file  STACK_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 *
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define STACK_MAX_OF_ENTRIES  5
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void (*STACK_PtrToFunction)(void * );
typedef STACK_PtrToFunction StackEntry_t;

typedef struct Stack
{
   int          StackTop;
   int          StackSize;
   StackEntry_t StackEntry[STACK_MAX_OF_ENTRIES];
}Stack_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function PrototyCopy_ptrToStackEntrys
*******************************************************************************/

void STACK_voidInitializeStack(Stack_t *Copy_ptrToStack);
u8   STACK_u8PushEntryElement(StackEntry_t Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack);
void STACK_u8PopEntryElement(StackEntry_t *Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack);
u8   STACK_u8IsStackEmpty(Stack_t *Copy_ptrToStack);
u8   STACK_u8IsStackFull(Stack_t *Copy_ptrToStack);
void STACK_voidClearStack(Stack_t *Copy_ptrToStack);
void STACK_voidRetrieveStackTop(StackEntry_t *Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack);
u8   STACK_u8ReturnStackSize(Stack_t *Copy_ptrToStack);

#endif /*File_H_*/

/*** End of File **************************************************************/
