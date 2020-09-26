/*******************************************************************************
* Title                 :   DWATCH 
* Filename              :   DWATCH_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   26/09/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  26/09/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file DWATCH_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DWATCH_interface.h"
#include "DWATCH_config.h"
#include "DWATCH_private.h"
#include "STK_interface.h"
#include "TFT_interface.h"

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
static u8  Static_u8Time[]     = "  :  :  ";
static u8  Static_u8Calender[] = "  /  /20  "; 
static u8  Static_u8Second;
static u8  Static_u8Minute;
static u8  Static_u8Hour;
static u8  Static_u8Day   = 1;
static u8  Static_u8Date  = 26;
static u8  Static_u8Month = 9;
static u16 Static_u16Year = 20;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void ADWATCH_voidCalCulateTime(void * Copy_VP)
{
   Static_u8Second++;
   if(Static_u8Second == 60)
   {
      Static_u8Second = 0;
      Static_u8Minute++;
   }
   if(Static_u8Minute == 60)
   {
      Static_u8Minute = 0;
      Static_u8Hour++;
   }
   if(Static_u8Hour == 24)
   {
      Static_u8Hour = 0;
      Static_u8Date++;
      Static_u8Day++;
   }
   if(Static_u8Day == 8)
   {
      Static_u8Day = 1;
   }
   if(Static_u8Date == 31)
   {
      Static_u8Date = 1;
      Static_u8Month++;
   }
   if(Static_u8Month == 13)
   {
      Static_u16Year++;
   }
   Static_u8Time[7]     = Static_u8Second % 10 + 48;
   Static_u8Time[6]     = Static_u8Second / 10 + 48;
   Static_u8Time[4]     = Static_u8Minute % 10 + 48;
   Static_u8Time[3]     = Static_u8Minute / 10 + 48;
   Static_u8Time[1]     = Static_u8Hour   % 10 + 48;
   Static_u8Time[0]     = Static_u8Hour   / 10 + 48;
   Static_u8Calender[9] = Static_u16Year  % 10 + 48;
   Static_u8Calender[8] = Static_u16Year  / 10 + 48;
   Static_u8Calender[4] = Static_u8Month  % 10 + 48;
   Static_u8Calender[3] = Static_u8Month  / 10 + 48;
   Static_u8Calender[1] = Static_u8Date   % 10 + 48;
   Static_u8Calender[0] = Static_u8Date   / 10 + 48;
}
void ADWATCH_voidDisplayDay(void)
{
   switch(Static_u8Day)
   {
      case 1:  HTFT_u8DrawText(35, 10, " SATURDAY  ", TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      case 2:  HTFT_u8DrawText(35, 10, " SUNDAY  "  , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      case 3:  HTFT_u8DrawText(35, 10, " MONDAY  "  , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      case 4:  HTFT_u8DrawText(35, 10, " TUESDAY "  , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      case 5:  HTFT_u8DrawText(35, 10, "WEDNESDAY"  , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      case 6:  HTFT_u8DrawText(35, 10, "THURSDAY "  , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
      default: HTFT_u8DrawText(35, 10, "FRIDAY "    , TFT_CYAN_COLOR, TFT_WHITE_COLOR, 1); break;
   }
}

void ADWATCH_voidDisplay(void)
{
   HTFT_u8DrawText(35, 27, Static_u8Calender, TFT_YELLOW_COLOR, TFT_WHITE_COLOR, 1);
   HTFT_u8DrawText(35, 50, Static_u8Time,     TFT_GREEN_COLOR,  TFT_WHITE_COLOR, 1);
}


/*************** END OF FUNCTIONS ***************************************************************************/
