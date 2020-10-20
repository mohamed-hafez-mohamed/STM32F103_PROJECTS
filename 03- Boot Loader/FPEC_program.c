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

/******************************************************************************
* Function : MFPEC_u8ProgramOneHalfWordFlash()
*//** 
* \b Description:
*
* This function is used to write code on the flash using flash driver peripheral. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  App area must be erased before writing op.
* 
* POST-CONDITION: None
*
* @param [in]     The address of the code line.
* @param [in]     Bytes of the code line.
* 
* @return 		   The state of writing done ornot.
*
* \b Example Example:
* @code
* 	MFPEC_u8ProgramOneHalfWordFlash(0x08001000, Code);
*
* @endcode
*
* @see MFPEC_u8ProgramOneHalfWordFlash
*
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
   // End of programming.
   SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PG);
}

/******************************************************************************
* Function : MFPEC_u8ProgramFlash()
*//** 
* \b Description:
*
* This function is used to write code on the flash using flash driver peripheral. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  App area must be erased before writing op.
* 
* POST-CONDITION: None
*
* @param [in]     The address of the beginning of the app area.
* @param [in]     An array that contain bytes that the code consists of.
* @param [in]     The number of half words that the array consists of.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_u8ProgramFlash(0x08001000, &Coderray, 16);
*
* @endcode
*
* @see MFPEC_u8ProgramFlash
*
*******************************************************************************/
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
      // End of programming.
      SET_BIT(FPEC->SR, EOP);
      CLR_BIT(FPEC->CR, PG);
   }
}

/******************************************************************************
* Function : MFPEC_voidErasePage()
*//** 
* \b Description:
*
* This function is used to erase page of the flash. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* 
* POST-CONDITION: None
*
* @param [in]     The page number.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_voidErasePage(16);
*
* @endcode
*
* @see MFPEC_voidErasePage
*
*******************************************************************************/
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
   // End of programming.
   SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PG);
}

/******************************************************************************
* Function : MFPEC_voidEraseAppArea()
*//** 
* \b Description:
*
* This function is used to erase the app area. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* PRE-CONDITION:  The first page number in app area must be defined in FPEC_config.
* PRE-CONDITION:  The last  page number in app area must be defined in FPEC_config.
* 
* POST-CONDITION: None
*
* @param [in]     void.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_voidEraseAppArea();
*
* @endcode
*
* @see MFPEC_voidEraseAppArea
*
*******************************************************************************/
void MFPEC_voidEraseAppArea(void)
{
   for(u8 Local_u8Page = FIRST_PAGE_NUMBER_IN_APP_AREA;Local_u8Page <= LAST_PAGE_NUMBER_IN_APP_AREA;Local_u8Page++)
   {
      MFPEC_voidErasePage(Local_u8Page);
   }
}

/******************************************************************************
* Function : MFPEC_voidErasePage()
*//** 
* \b Description:
*
* This function is used to erase the flash. 
*
* PRE-CONDITION:  Internal clock cycle must be enabled.
* 
* POST-CONDITION: None
*
* @param [in]     void.
* 
* @return 		   void.
*
* \b Example Example:
* @code
* 	MFPEC_voidEraseMass();
*
* @endcode
*
* @see MFPEC_voidEraseMass
*
*******************************************************************************/
void MFPEC_voidEraseMass(void)
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
   // Set the MER bit in the FLASH_CR register to select mass erasing.
   SET_BIT(FPEC->CR, MER);
   // Set the STRT bit in the FLASH_CR register to start mass erase operation.
   SET_BIT(FPEC->CR, STRT);
   /*Wait for the BSY bit to be reset*/
   while(GET_BIT(FPEC->SR, BSY) == SET);
   // End of programming.
   SET_BIT(FPEC->SR, EOP);
   CLR_BIT(FPEC->CR, PG);
}

/*************** END OF FUNCTIONS ***************************************************************************/
