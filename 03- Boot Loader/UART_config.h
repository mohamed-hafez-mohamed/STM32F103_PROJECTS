/****************************************************************************
* Title                 :   UART   
* Filename              :   UART_config.h
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
/** @file  UART_UART_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


// Baudrate Configuration
// Clock: 1 MHz 
#define UART_BAUDRATE_1200_CLK_1M       0X0341
#define UART_BAUDRATE_2400_CLK_1M       0X01A0
#define UART_BAUDRATE_4800_CLK_1M       0X00D0
#define UART_BAUDRATE_9600_CLK_1M       0X0068
#define UART_BAUDRATE_19200_CLK_1M      0X0034
// Clock: 8 MHz 
#define UART_BAUDRATE_1200_CLK_8M       0X1A0B
#define UART_BAUDRATE_2400_CLK_8M       0X0D05
#define UART_BAUDRATE_4800_CLK_8M       0X0683
#define UART_BAUDRATE_9600_CLK_8M       0X0341
#define UART_BAUDRATE_19200_CLK_8M      0X01A1
// Choose your BaudRate.
#define UART_BAUDRATE                   UART_BAUDRATE_9600_CLK_1M
/******************************************************************************
* Configuration Constants
*******************************************************************************/                          


/************************** Configuration data ********************************/

/**
* Defines two variables which specify the state of Uart.
*/
typedef enum 
{
   DISABLE_UART,                              /**<Disable uart */
	ENABLE_UART                                /**<Enable uart */
}UartState_t;

/**
* Defines two variables which specify number of data bits in the frame.
*/
typedef enum
{
	DATA_8BIT,                                 /**<8 data bits in the frame */    
	DATA_9BIT                                  /**<9 data bits in the frame */
}UartWordLength_t;

/**
* Defines three variables which specify parity in the frame.
*/
typedef enum
{
	NO_PARITY,                                  /**<No   parity in the frame */
   EVEN_PARITY,                                /**<Even parity in the frame */
	ODD_PARITY                                  /**<Odd  parity in the frame */
}UartParityMode_t;
/**
* Defines four variables which specify number of stop bits in the frame.
*/
typedef enum
{
   STOB_ONE_BIT,                                /**<One stop bit in the frame */
   STOB_HALF_BIT,                               /**<Half stop bit in the frame */     
   STOB_TWO_BITS,                               /**<Two and half stop bit in the frame */                     
   STOB_ONE_HALF_BIT                            /**<One and half stop bit in the frame */
}UartStopBits_t; 
/**
* Defines four variables which specify the uart mode.
*/
typedef enum
{
	ENABLE_RECEIVER = 1,                         /**<Uart works in receiver mode */
	ENABLE_TRANSMITTER,                          /**<Uart works in transmitter mode */
	ENABLE_BOTH                                  /**<Uart works in transmitter and receiver mode */
}UartMode_t;
/**
* Defines five variables which specify the uart configuration.
*/
typedef struct
{
	UartState_t           ModuleState;           /**<Uart Enable State */
	UartWordLength_t      WordLength;            /**<Define Word Length */
   UartStopBits_t        StopBits;              /**<Define Stob Bits Number */
	UartParityMode_t      ParityMode;            /**<Define Parity Mode */
	UartMode_t            RercSendState;         /**<Define Uart Mode */
	u32                   Baudrate ;             /**<Define Baud Rate */
}UartConfig_t;

// Configure Uart by choosing above variables.
static const UartConfig_t Static_UartConfig[NUMBER_OF_UART_CHANNELS] =
{
//    Uart        Data Bits  Stop Bits       Prity        UART      Baud Rate
//    State         Number    Number         State        MODE
//
   {ENABLE_UART,  DATA_8BIT, STOB_ONE_BIT, NO_PARITY, ENABLE_BOTH, UART_BAUDRATE},
   {DISABLE_UART, DATA_8BIT, STOB_ONE_BIT, NO_PARITY, ENABLE_BOTH, UART_BAUDRATE},
   {DISABLE_UART, DATA_8BIT, STOB_ONE_BIT, NO_PARITY, ENABLE_BOTH, UART_BAUDRATE}
};

#endif /*File_H_*/

/*** End of File **************************************************************/
