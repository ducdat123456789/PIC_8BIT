 /*
 * File            : spi.h
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Library for MPLAB XC8
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

#ifndef SPI_H
#define	SPI_H

#include <xc.h> 

/*
Spi_Type
	+ SPI_MASTER_OSC_DIV4 : To configure MSSP module as SPI Master with a clock of (Oscillator Frequency / 4).
	+ SPI_MASTER_OSC_DIV16 : To configure MSSP module as SPI Master with a clock of (Oscillator Frequency / 16).
	+ SPI_MASTER_OSC_DIV64 : To configure MSSP module as SPI Master with a clock of (Oscillator Frequency / 64).
	+ SPI_MASTER_TMR2 : To configure MSSP module as SPI Master with a clock generated by Timer 2 module.//Master clock source TMR2
	+ SPI_SLAVE_SS_EN : To configure MSSP module as SPI Slave with Slave Select input.
	+ SPI_SLAVE_SS_DIS : To configure MSSP module as SPI Slave without Slave Select input.
*/
typedef enum 
{
    SPI_MASTER_OSC_DIV4  = 0b00100000,
    SPI_MASTER_OSC_DIV16 = 0b00100001,
    SPI_MASTER_OSC_DIV64 = 0b00100010,
    SPI_MASTER_TMR2      = 0b00100011,
    SPI_SLAVE_SS_EN      = 0b00100100,
    SPI_SLAVE_SS_DIS     = 0b00100101
}Spi_Type;


/*
Spi_Data_Sample interval
	+ SPI_DATA_SAMPLE_MIDDLE : Input data is sampled at the middle of data output time.
	+ SPI_DATA_SAMPLE_END : Input data is sampled at the end of data output time
*/
typedef enum
{
    SPI_DATA_SAMPLE_MIDDLE   = 0b00000000,
    SPI_DATA_SAMPLE_END      = 0b10000000
}Spi_Data_Sample;


/*
Spi_Clock_Idle state
	+ SPI_CLOCK_IDLE_HIGH : Idle clock level is HIGH (1).
	+ SPI_CLOCK_IDLE_LOW : Idle clock level is LOW (0).
*/
typedef enum
{
    SPI_CLOCK_IDLE_HIGH  = 0b00010000,
    SPI_CLOCK_IDLE_LOW   = 0b00000000        
}Spi_Clock_Idle;


/*
Spi_Transmit_Edge
	+ SPI_IDLE_2_ACTIVE : Transmission occurs during transition from Idle to Active clock state.
	+ SPI_ACTIVE_2_IDLE : Transmission occurs during transition from Active to Idle clock state.
*/
typedef enum
{
    SPI_IDLE_2_ACTIVE    = 0b00000000,  //Data transmit on low to high edge	_SPI_LOW_2_HIGH
    SPI_ACTIVE_2_IDLE    = 0b01000000   //Data transmit on high to low edge	_SPI_HIGH_2_LOW
}Spi_Transmit_Edge;


void SPI_Init_Advanced(Spi_Type, Spi_Data_Sample, Spi_Clock_Idle, Spi_Transmit_Edge);
void SPI_Write(char);
unsigned int SPI_DataReady();
char SPI_Read();

#endif	/* SPI_H */

