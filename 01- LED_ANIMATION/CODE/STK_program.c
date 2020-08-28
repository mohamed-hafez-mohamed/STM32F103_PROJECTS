/*******************************************************************************
* Title                 :   STK 
* Filename              :   STK_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   26/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  26/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file STK_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"

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
static STK_PtrToFunction CallBackFunction;
static void * ParameterCallBack;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static u16 STK_u16ConfigIntervalMs(void)
{
    u32 Local_u32Clock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32Clock = AHP_CLOCK_FREQ / 8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32Clock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32Clock / STK_GENERATE_1_MS;
}

static u8 STK_u8ConfigIntervalUs(void)
{
    u32 Local_u32Clock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32Clock = AHP_CLOCK_FREQ / 8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32Clock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32Clock / STK_GENERATE_1_US;
}

void MSTK_voidInit(void)
{
    STK->CTRL  = STK_CLR_REG;
    STK->CTRL |= STK_CLOCK_SOURCE;
}

void MSTK_voidSetBusyWait_ms(u16 Copy_u16DelayMs)
{
    u16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    SET_BIT(STK->CTRL, ENABLE);
    while(GET_BIT(STK->CTRL, COUNTFLAG) == 0);
    CLR_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetBusyWait_us(u32 Copy_u32DelayUs)
{
    u8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u8Ticks * Copy_u32DelayUs;
    SET_BIT(STK->CTRL, ENABLE);
    while(GET_BIT(STK->CTRL, COUNTFLAG) == 0);
    CLR_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalSingle_ms(u16 Copy_u16DelayMs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    u16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    CallBackFunction  = Copy_PtrFunction;
    ParameterCallBack = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalSingle_us(u32 Copy_u32DelayUs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    u8 Local_u8Ticks = STK_u8ConfigIntervalUs;
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u8Ticks * Copy_u32DelayUs;
    CallBackFunction = Copy_PtrFunction;
    ParameterCallBack = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalPeriodic_ms(u16 Copy_u16DelayMs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    u16 Local_u16Ticks = STK_u16ConfigIntervalMs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u16Ticks * Copy_u16DelayMs) - STK_SUB_1_FOR_PERIODIC;
    CallBackFunction = Copy_PtrFunction;
    ParameterCallBack = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidSetIntervalPeriodic_us(u32 Copy_u32DelayUs, STK_PtrToFunction Copy_PtrFunction, void * Copy_Parameter)
{
    u8 Local_u8Ticks = STK_u8ConfigIntervalUs();
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = (Local_u8Ticks * Copy_u32DelayUs) - STK_SUB_1_FOR_PERIODIC;
    CallBackFunction = Copy_PtrFunction;
    ParameterCallBack = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}


u32  MSTK_u32GetElapsedTime_us(void)
{
    return (STK->LOAD - STK->VAL) * STK_u8ConfigIntervalUs();
}

u32  MSTK_u32GetElapsedTime_ms(void)
{
    return (STK->LOAD - STK->VAL) * STK_u16ConfigIntervalMs();
}

u32  MSTK_u32GetRemainingTime_us(void)
{
    return (STK->VAL) * STK_u8ConfigIntervalUs();
}

u32  MSTK_u32GetRemainingTime_ms(void)
{
    return (STK->VAL) * STK_u16ConfigIntervalMs();
}

void MSTK_voidStopStk(void)
{
    CLR_BIT(STK->CTRL, ENABLE);
	  CLR_BIT(STK->CTRL, TICKINT);
}

void MSTK_voidResumeStk(void)
{
    SET_BIT(STK->CTRL, ENABLE);
	  SET_BIT(STK->CTRL, TICKINT);
}

void SysTick_Handler(void)
{
    CallBackFunction(ParameterCallBack);
}

/*************************************** END OF FUNCTIONS **********************************************/
