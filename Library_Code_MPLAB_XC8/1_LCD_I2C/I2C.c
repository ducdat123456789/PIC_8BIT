#include"i2c_master.h"

void I2C_Init(const unsigned long I2C_BaudRate){
	/*
	Setup I2C (For Master Mode)
	*/
	SSPCON = 0x28;// Slew Rate control is disabled
	SSPCON2 = 0x00;
	SSPSTAT = 0x00;
	//SSPSTAT = 0x80;    // Slew Rate control is disabled
	SSPADD = (unsigned char)( _XTAL_FREQ/(4*I2C_BaudRate) ) - 1;
	TRISC3 = 1;// Make SDA and SCK pins input
	TRISC4 = 1;
}


/*
 the I2C_Wait() function which makes your master MCU sure that 
 the previous state has reached completion successfully and the bus is on IDLE,
  so it can proceed to the desired command.
*/
void I2C_Wait(){
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}


/*
Initiate An I2C Start Condition
*/
void I2C_Start(){
	//---[ Initiate I2C Start Condition Sequence ]---
	I2C_Wait();
	SEN = 1;
}


//Initiate An I2C Restart Condition		Repeated Start
void I2C_Restart(){
	//---[ Initiate I2C Restart Condition Sequence ]---
	I2C_Wait();
	RSEN = 1;
}


//Initiate An I2C Stop Condition
void I2C_Stop(){
	//---[ Initiate I2C Stop Condition Sequence ]---
	I2C_Wait();
	PEN = 1;
}

void I2C_ACK(void){
	/*
	Send ACK Signal (For Master Receiver Mode Only)
	*/
	ACKDT = 0; // 0 -> ACK
	I2C_Wait();
	ACKEN = 1; // Send ACK
}

void I2C_NACK(void){
	//Send NACK Signal (For Master Receiver Mode Only)
	ACKDT = 1; // 1 -> NACK
	I2C_Wait();
	ACKEN = 1; // Send NACK
}


//Send Byte Via I2C Bus, And Return The ACK/NACK From The Slave
unsigned char I2C_Write_Char(unsigned char Data){
  //---[ Send Byte, Return The ACK/NACK ]---
  I2C_Wait();
  SSPBUF = Data;
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0;
  return ACKSTAT;
}

//if ACK  -->char  ACK = 0
//if NACK -->char  ACK = 1
//Receive And Return A Byte From The I2C Bus
unsigned char I2C_Read_Char(char ACK){
    //---[ Receive & Return A Byte ]---
    uint8_t _data;
    I2C_Wait();
    RCEN = 1;        // Enable & Start Reception
    while(!SSPIF); // Wait Until Completion
  	SSPIF = 0; // Clear The Interrupt Flag Bit
    I2C_Wait();
    _data = SSPBUF;   
    I2C_Wait();
    if(ACK == 0)
       I2C_ACK();
    else
       I2C_NACK();
    
    return _data;	// Return The Received Byte
}

