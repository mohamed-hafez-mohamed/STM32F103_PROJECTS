/*******************************************************************************
* Title                 :   TL 
* Filename              :   TL_program.c
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
/** @file TL_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	
#include "stdlib.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TL_interface.h"
#include "TL_config.h"
#include "TL_private.h"
#include "STACK_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
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
static volatile       TLStates_t Static_StateVariable = STATE_1;
static Stack_t        Static_TrafficLineStack;
/*static StackEntry_t * Static_PtrToPtrToFunc4 = TL_voidRunState4; 
static StackEntry_t * Static_PtrToPtrToFunc3 = TL_voidRunState3;
static StackEntry_t * Static_PtrToPtrToFunc2 = TL_voidRunState2;
static StackEntry_t * Static_PtrToPtrToFunc1 = TL_voidRunState1; */
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void TL_voidInitializeTrafficLineStack(void)
{
   STACK_voidInitializeStack(&Static_TrafficLineStack);
   if(!STACK_u8IsStackFull(&Static_TrafficLineStack))
   {
      STACK_u8PushEntryElement(TL_voidRunState1,&Static_TrafficLineStack);
   }
   if(!STACK_u8IsStackFull(&Static_TrafficLineStack))
   {
      STACK_u8PushEntryElement(TL_voidRunState2,&Static_TrafficLineStack);
   }
   if(!STACK_u8IsStackFull(&Static_TrafficLineStack))
   {
      STACK_u8PushEntryElement(TL_voidRunState3,&Static_TrafficLineStack);
   }
   if(!STACK_u8IsStackFull(&Static_TrafficLineStack))
   {
      STACK_u8PushEntryElement(TL_voidRunState4,&Static_TrafficLineStack);
   }
}

void TL_voidRunState1(void * Copy_voidPointer)
{
   MGPIO_voidSetPinValue(PINA0, LOW);
   MGPIO_voidSetPinValue(PINA1, LOW);
   MGPIO_voidSetPinValue(PINA0, HIGH);
   MSTK_voidSetBusyWait_ms(1000);
   Static_StateVariable = STATE_2;
}

void TL_voidRunState2(void * Copy_voidPointer)
{
   MGPIO_voidSetPinValue(PINA1, HIGH);
   MSTK_voidSetBusyWait_ms(500);
   Static_StateVariable = STATE_3;
}

void TL_voidRunState3(void * Copy_voidPointer)
{
   MGPIO_voidSetPinValue(PINA0, LOW);
   MGPIO_voidSetPinValue(PINA1, LOW);
   MGPIO_voidSetPinValue(PINA2, HIGH);
   MSTK_voidSetBusyWait_ms(2000);
   Static_StateVariable = STATE_4;
}

void TL_voidRunState4(void * Copy_voidPointer)
{  
   MGPIO_voidSetPinValue(PINA2, LOW);
   MGPIO_voidSetPinValue(PINA1, HIGH);
   MSTK_voidSetBusyWait_ms(1000);
   Static_StateVariable = STATE_1;
}

void TL_voidRunTlSystem(void)
{
   StackEntry_t Local_CallBackFunction;
   Local_CallBackFunction = (Static_TrafficLineStack.StackEntry[Static_StateVariable]);
   Local_CallBackFunction(NULL);
}
/*************** END OF FUNCTIONS ***************************************************************************/
