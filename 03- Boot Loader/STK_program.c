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
static STK_PtrToFunction CallBackFunction[4];
static void * ParameterCallBack[4];
static u8 Static_u8SingleUs;
static u8 Static_u8PeriodcUs;
static u8 Static_u8SingleMs;
static u8 Static_u8PeriodicMs;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static u16 STK_u16ConfigIntervalMs(void)
{
    u32 Local_u32STKClock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32STKClock = AHP_CLOCK_FREQ / STK_DIVIDE_AHP_BY_8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE
        Local_u32STKClock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32STKClock / STK_GENERATE_1_MS;
}

static u8 STK_u8ConfigIntervalUs(void)
{
    u32 Local_u32STKClock;
    #if   STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE_DIV_8
        Local_u32STKClock = AHP_CLOCK_FREQ / STK_DIVIDE_AHP_BY_8;
    #elif STK_CLOCK_SOURCE == STK_AHB_CLOCK_SOURCE
        Local_u32STKClock = AHP_CLOCK_FREQ;
    #else
        //!<TODO: Error Code
    #endif
    return Local_u32STKClock / STK_GENERATE_1_US;
}

void MSTK_voidInit(void)
{
    STK->CTRL  = STK_CLR_REG;
    STK->CTRL |= STK_CLOCK_SOURCE;
    Static_u8SingleUs   = 0;
    Static_u8PeriodcUs  = 0;
    Static_u8SingleMs   = 0;
    Static_u8PeriodicMs = 0;
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
    CLR_BIT(STK->CTRL, ENABLE);
    STK->VAL  = STK_CLR_REG;
    STK->LOAD = Local_u16Ticks * Copy_u16DelayMs;
    Static_u8SingleMs = 1;
    CallBackFunction[1]  = Copy_PtrFunction;
    ParameterCallBack[1] = Copy_Parameter;
    SET_BIT(STK->CTRL, TICKINT);
    SET_BIT(STK->CTRL, ENABLE);
}

void MSTK_voidStopStk(void)
{
    CLR_BIT(STK->CTRL, ENABLE);
	CLR_BIT(STK->CTRL, TICKINT);
}

void SysTick_Handler(void)
{
    if(Static_u8SingleUs == 1)
    {
        CallBackFunction[0](ParameterCallBack[0]);
        Static_u8SingleUs = 0;
    }
    if(Static_u8SingleMs == 1)
    {
        CallBackFunction[1](ParameterCallBack[1]);
        Static_u8SingleMs = 0;
    }
    if(Static_u8PeriodcUs == 1)
    {
        CallBackFunction[2](ParameterCallBack[2]);
    }
    if(Static_u8PeriodicMs == 1)
    {
        CallBackFunction[3](ParameterCallBack[3]);
    }
}

/*************************************** END OF FUNCTIONS **********************************************/
