#include "include\define.h"

enum {
    TEMP, HUMI
};

//**********************************************************************************
//*
//*		 writes a byte on the Sensibus and checks the acknowledge 
//*
//**********************************************************************************

char s_write_byte(unsigned char value) {
    unsigned char i, error = 0;

    SDA = 0;
    SDAdir = 0; // define SDA as output
    SCL = 0; // SCL low
    for (i = 0x80; i > 0; i /= 2) // repeat 8 times
    {
        if (i & value) SDA = 1; // if bit 7 = 1
        else SDA = 0;

        DelayMs(1); // 1us delay
        SCL = 1; // SCL high
        DelayMs(1); // 1us delay
        SCL = 0; // SCL low
    }

    DelayMs(1);
    SDAdir = 1; // define SDA as input
    SCL = 1; // SCL high
    DelayMs(1); // 1us delay
    error = SDA;
    SCL = 0; // 1us delay
    DelayMs(1); // 1us delay
    return error; //error=1 in case of no acknowledge
}

//**********************************************************************************
//*
//*		 reads a byte form the Sensibus and gives an acknowledge in case of "ack=1" 
//*
//**********************************************************************************

char s_read_byte(unsigned char ack) {
    unsigned char i, val = 0;
    for (i = 0x80; i > 0; i /= 2) //shift bit for masking
    {
        SCL = 1;
        DelayMs(1); //clk for SENSI-BUS
        if (SDA) val = (val | i); //read bit
        SCL = 0;
        DelayMs(1);
    }

    SDA = !ack;
    SDAdir = OUT;

    DelayMs(1); //in case of "ack==1" pull down DATA-Line
    SCL = 1; //clk #9 for ack
    DelayMs(1);
    SCL = 0;
    DelayMs(1);
    SDA = 1;
    SDAdir = IN; //release DATA-line
    return val;
}

//**********************************************************************************
//*
//*		generates a transmission start 
//*      		_____         ________
//*		DATA:        |_______|
//*           		___     ___
//* 	SCK : 	___|   |___|   |______
//*
//**********************************************************************************

void s_transstart(void) {
    SDA = 1;
    SDAdir = 1;
    DelayMs(1); // define SDA as input
    SCL = 1; // SCL high
    DelayMs(1); // 1us delay
    SDAdir = 0; // define SDA as output !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    SDA = 0; // SDA low!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    DelayMs(1); // 1us delay
    SCL = 0; // SCL low
    DelayMs(1); // 1us delay
    SCL = 1; // SCL high
    DelayMs(1); // 1us delay
    SDA = 1;
    SDAdir = 1; // define SDA as input
    DelayMs(1); // 1us delay
    SCL = 0; // SCL low
}

//**********************************************************************************
//*
//* communication reset: DATA-line=1 and at least 9 SCK cycles and trans start
//*       ____________________________________________________       _____
//* DATA:                                                     |_____| 
//*          _    _    _    _    _    _    _    _    _       ___    ___
//* SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |_____|   |__|   |___
//*
//**********************************************************************************

void s_connectionreset(void) {
    unsigned char i;
    TRISBbits.TRISB8 = 0;
    SDA = 1;
    TRISBbits.TRISB9 = 1;

    LATBbits.LATB8 = 0; // SCL low
    SDAdir = 1; // define SDA as input
    for (i = 1; i <= 18; i++) { // repeat 18 times
        if (LATBbits.LATB8) LATBbits.LATB8 = 0;
        else LATBbits.LATB8 = 1;
        DelayMs(1);
    } // invert SCL

    //	s_transstart();                   //transmission start????????????????????????????????????????????
}

//**********************************************************************************
//*
//* resets the sensor by a softreset 
//*
//**********************************************************************************
/*
char s_softreset(void)
{ 
        unsigned char error=0;
        s_connectionreset();              //reset communication
        error+=s_write_byte(RESET);       //send RESET-command to sensor
        return error;                     //error=1 in case of no response form the sensor
}

//**********************************************************************************
//*
//* reads the status register with checksum (8-bit)
//*
//**********************************************************************************

char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
{ 
        unsigned char error=0;
        s_transstart();                   //transmission start
        error=s_write_byte(STATUS_REG_R); //send command to sensor
 *p_value=s_read_byte(ACK);        //read status register (8-bit)
 *p_checksum=s_read_byte(noACK);   //read checksum (8-bit)
        return error;                     //error=1 in case of no response form the sensor
}

//**********************************************************************************
//*
//* writes the status register with checksum (8-bit)
//*
//**********************************************************************************

char s_write_statusreg(unsigned char *p_value)
{ 
        unsigned char error=0;
        s_transstart();                   //transmission start
        error+=s_write_byte(STATUS_REG_W);//send command to sensor
        error+=s_write_byte(*p_value);    //send value of status register
        return error;                     //error>=1 in case of no response form the sensor
}
 							   
 */
//**********************************************************************************
//*
//* makes a measurement (humidity/temperature) with checksum
//*
//**********************************************************************************

char SHT_measure(char *Th, char *Tl, char *Hh, char *Hl) { //lásd.:http://www.eet.bme.hu/~czirkos/referenciak.php

    unsigned int i;
    unsigned char error = 0;
//    union int_char tempraw, humiraw;

    s_connectionreset(); //??????????????????????????????????????????????
    s_transstart(); //transmission start
    DelayMs(1);

    error += s_write_byte(MEASURE_TEMP);
    DelayMs(10);
    for (i = 0; i < 65535; i++) if (SDA == 0) break; //wait until sensor has finished the measurement
    if (SDA == 1) error += 1; // or timeout (~2 sec.) is reached

    *Th = s_read_byte(ACK);
    *Tl = s_read_byte(noACK); //read the second byte (LSB)
    //	c = s_read_byte(noACK);  //read checksum

    s_connectionreset(); //????????????????????????????????????????????
    s_transstart(); //transmission start
    DelayMs(1);
    error += s_write_byte(MEASURE_HUMI);
    DelayMs(10);
    for (i = 0; i < 65535; i++) if (SDA == 0) break; //wait until sensor has finished the measurement
    if (SDA == 1) error += 1; // or timeout (~2 sec.) is reached

    *Hh = s_read_byte(ACK);
    *Hl = s_read_byte(noACK); //read the second byte (LSB)
    //	c = s_read_byte(noACK);  //read checksum

    return error;
}



