/*******************************************************************************
* Title                 :   STACK
* Filename              :   STACK_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   30/01/2021
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description
*  30/01/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file STACK_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO?
 */
/******************************************************************************
* Includes
*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STACK_config.h"
#include "STACK_private.h"
#include "STACK_interface.h"
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

void STACK_voidInitializeStack(Stack_t *Copy_ptrToStack)
{
   Copy_ptrToStack->StackTop  = 0;
   Copy_ptrToStack->StackSize = 0;
}

u8 STACK_u8PushEntryElement(StackEntry_t Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack)
{
   Copy_ptrToStack->StackEntry[Copy_ptrToStack->StackTop++] = Copy_ptrToStackEntry;
   Copy_ptrToStack->StackSize++;
}

void STACK_u8PopEntryElement(StackEntry_t *Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack)
{
   *Copy_ptrToStackEntry = Copy_ptrToStack->StackEntry[--Copy_ptrToStack->StackTop];
   Copy_ptrToStack->StackSize--;
}

u8  STACK_u8IsStackEmpty(Stack_t *Copy_ptrToStack)
{
   return  !Copy_ptrToStack->StackSize;
}

u8  STACK_u8IsStackFull(Stack_t *Copy_ptrToStack)
{
   return Copy_ptrToStack->StackTop == STACK_MAX_OF_ENTRIES;
}

void STACK_voidClearStack(Stack_t *Copy_ptrToStack)
{
   Copy_ptrToStack->StackTop = 0;
}
void STACK_voidRetrieveStackTop(StackEntry_t *Copy_ptrToStackEntry,Stack_t *Copy_ptrToStack)
{
   *Copy_ptrToStackEntry = Copy_ptrToStack->StackEntry[Copy_ptrToStack -> StackTop - 1];
}

u8  STACK_u8ReturnStackSize(Stack_t *Copy_ptrToStack)
{
   return Copy_ptrToStack->StackSize;
}


/*************** END OF FUNCTIONS ***************************************************************************/
