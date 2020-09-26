/*******************************************************************************
* Title                 :   TFT 
* Filename              :   TFT_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   21/9/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  21/9/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file TFT_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"

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
static u16 Static_u16ColStart;
static u16 Static_u16RowStart;
static u16 Static_u16Wrap = 1;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void HTFT_voidWriteCommand(u8 Copy_u8Command)
{
   MGPIO_voidSetPinValue(TFT_A0_PIN, LOW);
   MSPI1_voidSendReceiveSync(0, Copy_u8Command);
}

static void HTFT_voidWriteData(u8 Copy_u8Data)
{
   MGPIO_voidSetPinValue(TFT_A0_PIN, HIGH);
   MSPI1_voidSendReceiveSync(0, Copy_u8Data);
}

static void HTFT_voidSetAddWindow(u8 Copy_u8Width1, u8 Copy_u8Width2, u8 Copy_u8Height1, u8 Copy_u8Height2)
{
	HTFT_voidWriteCommand(TFT_CASET_CMD);                         //Coloumn set address command
	HTFT_voidWriteData(0);                                        //Coloumn set address parameter MSB START
	HTFT_voidWriteData(Copy_u8Width1);                            //Coloumn set address parameter LSB START
	HTFT_voidWriteData(0);                                        //Coloumn set address parameter MSB END
	HTFT_voidWriteData(Copy_u8Width2 + Static_u16ColStart);       //Coloumn set address parameter LSB END
	HTFT_voidWriteCommand(TFT_RASET_CMD);                         //Row set address command
	HTFT_voidWriteData(0);                                        //Row set address parameter MSB START
	HTFT_voidWriteData(Copy_u8Height1);                           //Row set address parameter LSB START
	HTFT_voidWriteData(0);                                        //Row set address parameter MSB END
	HTFT_voidWriteData(Copy_u8Height2 + Static_u16RowStart);      //Row set address parameter LSB END

	HTFT_voidWriteCommand(TFT_RAMWR_CMD);                         //RAM Write
}

void HTFT_voidInit(void)
{
	//RESET PULSE
   MGPIO_voidSetPinValue(TFT_RST_PIN, HIGH);
   MSTK_voidSetBusyWait_us(100);
   MGPIO_voidSetPinValue(TFT_RST_PIN, LOW);
   MSTK_voidSetBusyWait_us(1);
   MGPIO_voidSetPinValue(TFT_RST_PIN, HIGH);
   MSTK_voidSetBusyWait_us(100);
   MGPIO_voidSetPinValue(TFT_RST_PIN, LOW);
   MSTK_voidSetBusyWait_us(100);
   MGPIO_voidSetPinValue(TFT_RST_PIN, HIGH);
   MSTK_voidSetBusyWait_ms(120);
   //Commands
   HTFT_voidWriteCommand(TFT_SLPOUT_CMD);     //To Out from sleeping mode
   MSTK_voidSetBusyWait_ms(150);
   HTFT_voidWriteCommand(TFT_COLMOD_CMD);     //Color Mode
   HTFT_voidWriteData(TFT_COLOR_MODE);        //Command Parameter              
   HTFT_voidWriteCommand(TFT_DISPON_CMD);     //TFT Display on
}

void HTFT_voidDisplayImage(const u16 * Copy_u16Image)
{
	HTFT_voidSetAddWindow(0, TFT_WIDTH_SIZE, 0, TFT_HEIGHT_SIZE);
	for(u16 Local_u16Counter = 0;Local_u16Counter < (TFT_WIDTH * TFT_HEIGHT);Local_u16Counter++)
	{
	   HTFT_voidWriteData(Copy_u16Image[Local_u16Counter] >> TFT_get_HIGH_BYTE);
		HTFT_voidWriteData(Copy_u16Image[Local_u16Counter] &  TFT_GET_LOW_BYTE);
	}
}
u8 HTFT_u8DrawPixel(u16 Copy_u16Width, u16 Copy_u16Height, u16  Copy_u16Color)
{
   if((Copy_u16Width >= TFT_WIDTH) || (Copy_u16Height >= TFT_HEIGHT))
	{
		return 1;
	}
	HTFT_voidSetAddWindow(Copy_u16Width,Copy_u16Width + 1,Copy_u16Height,Copy_u16Height + 1);
	HTFT_voidWriteData(Copy_u16Color >> TFT_get_HIGH_BYTE);
	HTFT_voidWriteData(Copy_u16Color &  TFT_GET_LOW_BYTE);
}

u8 HTFT_u8FillRectangle(u16 Copy_u16Width1, u16 Copy_u16Width2, u16 Copy_u16Height1, u16 Copy_u16Height2, u16  Copy_u16Color)
{
	u16 Local_u16HighByte;
	u16 Local_u16LowByte;
	if((Copy_u16Width1 >= TFT_WIDTH) || (Copy_u16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_u16Width1 + Copy_u16Width2 - 1) >= TFT_WIDTH)  
	{
		Copy_u16Width2 = TFT_WIDTH  - Copy_u16Width1;
	}
   if((Copy_u16Height1 + Copy_u16Height2 - 1) >= TFT_HEIGHT) 
	{
		Copy_u16Height2 = TFT_HEIGHT - Copy_u16Height1;
	}
	u16 Local_u16Size = (Copy_u16Width2 - Copy_u16Width1 - 1) * (Copy_u16Height2 * Copy_u16Height1 - 1);
   HTFT_voidSetAddWindow(Copy_u16Width1,Copy_u16Width1+Copy_u16Width2-1,Copy_u16Height1,Copy_u16Height1+Copy_u16Height2-1);
   Local_u16HighByte = Copy_u16Color >> TFT_get_HIGH_BYTE;
	Local_u16LowByte  = Copy_u16Color &  TFT_GET_LOW_BYTE;
	for(u16 Local_u16Counter = 0;Local_u16Counter < Local_u16Size;Local_u16Counter++)
	{
	   HTFT_voidWriteData(Local_u16HighByte);
		HTFT_voidWriteData(Local_u16LowByte);
	}
}

u8 HTFT_u8FillColour(u16  Copy_u16Color)
{
	return HTFT_u8FillRectangle(0, TFT_WIDTH_SIZE, 0, TFT_HEIGHT_SIZE, Copy_u16Color);
}

u8 HTFT_u8DrawFastVLine(u16 Copy_u16Width1, u16 Copy_u16Height1, u16 Copy_u16Height2, u16  Copy_u16Color)
{
	u16 Local_u16HighByte;
	u16 Local_u16LowByte;
	if((Copy_u16Width1 >= TFT_WIDTH) || (Copy_u16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_u16Height1 + Copy_u16Height2 - 1) >= TFT_HEIGHT) 
	{
		Copy_u16Height2 = TFT_HEIGHT - Copy_u16Height1;
	}
	Local_u16HighByte = Copy_u16Color >> TFT_get_HIGH_BYTE;
	Local_u16LowByte  = Copy_u16Color &  TFT_GET_LOW_BYTE;
	HTFT_voidSetAddWindow(Copy_u16Width1,Copy_u16Width1,Copy_u16Height1,Copy_u16Height1+Copy_u16Height2-1);
	while(Copy_u16Height2--)
	{
		HTFT_voidWriteData(Local_u16HighByte);
		HTFT_voidWriteData(Local_u16LowByte);
	}
}

u8 HTFT_u8DrawFastHLine(u16 Copy_u16Width1, u16 Copy_u16Width2,  u16 Copy_u16Height1, u16  Copy_u16Color)
{
	u16 Local_u16HighByte;
	u16 Local_u16LowByte;
	if((Copy_u16Width1 >= TFT_WIDTH) || (Copy_u16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_u16Width1 + Copy_u16Width2 - 1) >= TFT_HEIGHT) 
	{
		Copy_u16Width2 = TFT_WIDTH - Copy_u16Width1;
	}
	Local_u16HighByte = Copy_u16Color >> TFT_get_HIGH_BYTE;
	Local_u16LowByte  = Copy_u16Color &  TFT_GET_LOW_BYTE;
	HTFT_voidSetAddWindow(Copy_u16Width1,Copy_u16Width1+Copy_u16Width2-1,Copy_u16Height1,Copy_u16Height1);
	while(Copy_u16Width2--)
	{
		HTFT_voidWriteData(Local_u16HighByte);
		HTFT_voidWriteData(Local_u16LowByte);
	}
}

u8 HTFT_u8DrawRectangle(u16 Copy_u16Width1, u16 Copy_u16Width2, u16 Copy_u16Height1, u16 Copy_u16Height2, u16  Copy_u16Color)
{
	HTFT_u8DrawFastHLine(Copy_u16Width1, Copy_u16Width2, Copy_u16Height1, Copy_u16Color);
	HTFT_u8DrawFastHLine(Copy_u16Width1, Copy_u16Width2, Copy_u16Height1+Copy_u16Height2-1, Copy_u16Color);
	HTFT_u8DrawFastVLine(Copy_u16Width1, Copy_u16Height1, Copy_u16Height2, Copy_u16Color);
	HTFT_u8DrawFastVLine(Copy_u16Width1+Copy_u16Width2-1, Copy_u16Height1, Copy_u16Height2, Copy_u16Color);
}

u8 HTFT_u8FillRect(u16 Copy_u16Width1, u16 Copy_u16Width2, u16 Copy_u16Height1, u16 Copy_u16Height2, u16  Copy_u16Color)
{
	for (s16 Local_s16Counter = Copy_u16Width1;Local_s16Counter < Copy_u16Width1 + Copy_u16Width2;Local_s16Counter++)
	{
		HTFT_u8DrawFastVLine(Local_s16Counter, Copy_u16Height1, Copy_u16Height2, Copy_u16Color);
   }
}

u8 HTFT_u8DrawCircle(s16 Copy_s16Width, s16 Copy_s16Height, s16 Copy_s16Radius,u16 Copy_u16Color)
{
	s16 Local_s16F = 1 - Copy_s16Radius;
	s16 Local_s16ddF_x = 1;
	s16 Local_s16ddF_y = -2 * Copy_s16Radius;
	s16 Local_s16X = 0;
	s16 Local_s16Y = Copy_s16Radius;
	HTFT_u8DrawPixel(Copy_s16Width, Copy_s16Height + Copy_s16Radius, Copy_u16Color);
	HTFT_u8DrawPixel(Copy_s16Width, Copy_s16Height - Copy_s16Radius, Copy_u16Color);
	HTFT_u8DrawPixel(Copy_s16Width + Copy_s16Radius, Copy_s16Height, Copy_u16Color);
	HTFT_u8DrawPixel(Copy_s16Width - Copy_s16Radius, Copy_s16Height, Copy_u16Color);
	while(Local_s16X < Local_s16Y)
	{
		if(Local_s16F >= 0)
		{
			Local_s16Y--;
			Local_s16ddF_y += 2;
			Local_s16F += Local_s16ddF_y;
		}
		Local_s16X++;
		Local_s16ddF_x += 2;
      Local_s16F += Local_s16ddF_x;
		HTFT_u8DrawPixel(Copy_s16Width + Local_s16X, Copy_s16Height + Local_s16Y, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width - Local_s16X, Copy_s16Height + Local_s16Y, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width + Local_s16X, Copy_s16Height - Local_s16Y, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width - Local_s16X, Copy_s16Height - Local_s16Y, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width + Local_s16Y, Copy_s16Height + Local_s16X, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width - Local_s16Y, Copy_s16Height + Local_s16X, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width + Local_s16Y, Copy_s16Height - Local_s16X, Copy_u16Color);
		HTFT_u8DrawPixel(Copy_s16Width - Local_s16Y, Copy_s16Height - Local_s16X, Copy_u16Color);
	}
}

u8 HTFT_u8DrawChar(u8 Copy_u8Width, u8 Copy_u8Height, u8 Copy_u8Char,u16 Copy_u16Color, u16 Copy_u16Bg, u16 Copy_u16Size)
{
	if((Copy_u8Width >= TFT_WIDTH) || (Copy_u8Height >= TFT_HEIGHT))
	{
		return 1;
	}
	if(Copy_u16Size < 1) Copy_u16Size = 1;
	if((Copy_u8Char < ' ') || (Copy_u8Char > '~')) Copy_u8Char = '?';
   for(u8 Local_u8Counter1 = 0; Local_u8Counter1 < 5; Local_u8Counter1++ )
	{
		u8 Local_u8Line;
		if(Copy_u8Char < 'S') Local_u8Line = Const_Font1[(Copy_u8Char - 32)  * 5 + Local_u8Counter1];
		else                  Local_u8Line = Const_Font2[(Copy_u8Char - 'S') * 5 + Local_u8Counter1];
      for(u8 Local_u8Counter2 = 0;Local_u8Counter2 < 7;Local_u8Counter2++,Local_u8Line>>= 1)
		{
			if(Local_u8Line & 0X01)
			{
				if(Copy_u16Size == 1)
				{
					HTFT_u8DrawPixel(Copy_u8Width + Local_u8Counter1, Copy_u8Height + Local_u8Counter2, Copy_u16Color);
				}
				else
				{
					HTFT_u8FillRect(Copy_u8Width+Local_u8Counter1*Copy_u16Size,Copy_u8Height+Local_u8Counter2*Copy_u16Size,Copy_u16Size,Copy_u16Size,Copy_u16Color);
				}
			}
			else if(Copy_u16Bg != Copy_u16Color)
			{
				if(Copy_u16Size == 1)
				{
           HTFT_u8DrawPixel(Copy_u8Width + Local_u8Counter1, Copy_u8Height + Local_u8Counter2, Copy_u16Bg);
				}
				else
				{
					 HTFT_u8FillRect(Copy_u8Width+Local_u8Counter1*Copy_u16Size,Copy_u8Height+Local_u8Counter2*Copy_u16Size,Copy_u16Size,Copy_u16Size,Copy_u16Bg);
				}
			}
		}
	}
}

u8 HTFT_u8DrawText(u8 Copy_u8Width, u8 Copy_u8Height, u8 * Copy_u8Text,u16 Copy_u16Color, u16 Copy_u16Bg, u16 Copy_u16Size)
{
	u8  Local_u8CursorX   = Copy_u8Width;
	u8  Local_u8CursorY   = Copy_u8Height;
	u16 Local_u16TextSize = strlen(Copy_u8Text);
	for(u16 Local_u16Counter = 0;Local_u16Counter < Local_u16TextSize;Local_u16Counter++)
	{
		if(Static_u16Wrap && (Local_u8CursorX + Copy_u16Size * 5) > TFT_WIDTH)
		{
			Local_u8CursorX = 0;
			Local_u8CursorY = Local_u8CursorY + Copy_u16Size * 7 + 3;
			if(Local_u8CursorY > TFT_HEIGHT) Local_u8CursorY = TFT_HEIGHT;
         if(Copy_u8Text[Local_u16Counter] == 0x20) goto _Skip;
		}
		HTFT_u8DrawChar(Local_u8CursorX,Local_u8CursorY,Copy_u8Text[Local_u16Counter],Copy_u16Color,Copy_u16Bg,Copy_u16Size);
    Local_u8CursorX = Local_u8CursorX + Copy_u16Size * 6;
    if(Local_u8CursorX > TFT_WIDTH) Local_u8CursorX = TFT_WIDTH;
    _Skip:;
	}
}


/*************** END OF FUNCTIONS ***************************************************************************/
