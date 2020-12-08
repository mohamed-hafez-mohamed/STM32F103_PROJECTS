/*******************************************************************************
* Title                 :   FPEC 
* Filename              :   FPEC_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   13/10/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  13/10/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file FPEC_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "FPEC_interface.h"
#include "FPEC_config.h"
#include "FPEC_private.h"

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
u8 MFPEC_u8ProgramHalfWordFlash(u32 Copy_u32Address, u16 Copy_u16Code)
{
   u8 Local_u8WritingState = 0;
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
      // Perform Unlock Sequence To Unlock FPEC Peripheral.
      FPEC->KEYR = FPEC_KEY_1;
      FPEC->KEYR = FPEC_KEY_2;
   }
   // Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Set the PG bit in the FLASH_CR register.
   SET_BIT(FPEC->CR, PG);
   // Perform the data write (half-word) at the desired address.
   *((volatile u16*)(Copy_u32Address)) = Copy_u16Code;
   // Wait for the BSY bit to be reset.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   CLR_BIT(FPEC->CR, PG);
}

void MFPEC_u8ProgramFlash(u32 Copy_u32Address, u16 * Copy_u16Code, u8 Copy_u8Length)
{
   // Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
      // Perform Unlock Sequence To Unlock FPEC Peripheral.
      FPEC->KEYR = FPEC_KEY_1;
      FPEC->KEYR = FPEC_KEY_2;
   }
   for(u8 Local_u8Index = 0;Local_u8Index < Copy_u8Length;Local_u8Index++)
   {
      // Set the PG bit in the FLASH_CR register to write on the flash.
      SET_BIT(FPEC->CR, PG);
      // Half word write operation.
      *((volatile u16*)(Copy_u32Address)) = Copy_u16Code[Local_u8Index];
      Copy_u32Address += TWO_BYTE;
      // Wait for the BSY bit to be reset.
      while(GET_BIT(FPEC->SR, BSY) == SET);

      CLR_BIT(FPEC->CR, PG);
   }
}

void MFPEC_voidErasePage(u16 Copy_u16PageNumber)
{
   // Check that no main Flash memory operation is ongoing.
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // Check if the flash locked or not.
   if(GET_BIT(FPEC->CR, LOCK) == SET)
   {
      // Perform Unlock Sequence To Unlock FPEC Peripheral.
      FPEC->KEYR = FPEC_KEY_1;
      FPEC->KEYR = FPEC_KEY_2;
   }
   // Set the PER bit in the FLASH_CR register to erase page.
   SET_BIT(FPEC->CR, PER);
   // Program the FLASH_AR register to select a page to erase.
   FPEC->AR = FLASH_START_ADDRESS + (u32)(Copy_u16PageNumber * PAGE_SIZE);
   // Set the STRT bit in the FLASH_CR register to start erase operation.
   SET_BIT(FPEC->CR, STRT);
   /*Wait for the BSY bit to be reset*/
   while(GET_BIT(FPEC->SR, BSY) == SET);

   CLR_BIT(FPEC->CR, PER);
}
void MFPEC_voidEraseAppArea(u16 Copy_u16FirstPageNumber, u16 Copy_u16LastPageNumber)
{
   for(u8 Local_u8Page = Copy_u16FirstPageNumber;Local_u8Page <= Copy_u16LastPageNumber;Local_u8Page++)
   {
      MFPEC_voidErasePage(Local_u8Page);
   }
}

/*************** END OF FUNCTIONS ***************************************************************************/
