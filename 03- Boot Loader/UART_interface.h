/****************************************************************************
* Title                 :   UART   
* Filename              :   UART_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   19/09/2020
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
*  19/09/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  UART_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// UART Pins Without Mapping.
#define UART_1_TX                  PINA9
#define UART_1_RX                  PINA10
#define UART_2_TX                  PINA2
#define UART_2_RX                  PINA3
#define UART_3_TX                  PINB10
#define UART_3_RX                  PINB11
//Different Modes
#define CLOCK_PHASE_CAP_FIRST      0
#define CLOCK_PHASE_CAP_SECOND     1
#define CLOCK_POLARITY_LOW         0
#define CLOCK_POLARITY_HIGH        1
// Applying Clock Phase and Clock Ploarity Mode.
#define CLOCK_PHASE                  CLOCK_PHASE_CAP_SECOND
#define CLOCK_POLARITY               CLOCK_POLARITY_LOW 
/**
* Defines four variables which specify the uart.
*/
typedef enum
{
   UART1,                          /**<Uart 1*/
   UART2,                          /**<Uart 2*/
   UART3,                          /**<Uart 3*/
   NUMBER_OF_UART_CHANNELS         /**<Uarts on the microcontroller*/
}UartChannels_t;


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MUART_voidInit(void);
void MUART_voidTransmitSynch(UartChannels_t Copy_u8UartNumber, u8 Copy_u8DataArray[]);
u8   MUART_u8ReceiveByteSynch(UartChannels_t Copy_u8UartNumber);
u8   MUART_u8ReceiveSynch(UartChannels_t Copy_u8UartNumber, u8 * Copy_u8Data);
void MUART_voidReceiveASynch(UartChannels_t Copy_u8UartNumber, void (*CallBackFuncRx)(u8));

#endif /*File_H_*/

/*** End of File **************************************************************/
