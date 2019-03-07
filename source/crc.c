//#include<p24fxxxx.h>
#include "include\define.h"
    
    /*********************************************************************
     * WORD CRC16(  INPUT unsigned char * data, 
     *              INPUT signed char dataLength, 
     *              INPUT WORD initCRC)
     *
     * Overview:        This function generates 16-bit CRC code for the input 
     *                  data, with initial CRC value 
     *
     * PreCondition:    None
     *
     * Input:       
     *          unsigned char *      data        The input buffer to generate CRC 
     *                                  code from.
     *          signed char dataLength  The size of input data buffer 
     *          WORD        initCRC     The initial value of CRC. The 
     *                                  initial CRC value enables the
     *                                  CRC generate module generates 
     *                                  CRC block by block
     * Output:          
     *          WORD                    Generated CRC code
     *
     * Side Effects:    None
     * 
     ********************************************************************/
    WORD CRC16(unsigned char *ptr, signed char count)
    {
        WORD crc;
        unsigned char i;
    
        crc = 0;
        while(--count >= 0 )
        {
            crc = crc ^ ((WORD) *ptr++ << 8);
            for(i = 0; i < 8; i++)
            {
                if( crc & 0x8000 )
                {
                    crc = (crc << 1) ^ 0x1021;
                }
                else
                {
                    crc = crc << 1;
                }   
            }
        }
    
        return crc;
    }

//*********************************************************************************
//*
//*********************************************************************************
unsigned int CRC_HW_calculateB(unsigned char *temp,unsigned int Len)
{
	unsigned int Carry,j;
	unsigned char *ptr,Flag;
	
	ptr=(unsigned char *)&CRCDAT;
	
	CRCCON = 0x0000F; // ="Length of polynomial-1"
	CRCXOR = 0x1021; // generator Polynomial
	CRCWDAT= 0x0000; // Initialize CRCWDAT with 0
	Flag=0x00;
	
	for(j=0;j<Len;j++)
	{
		*ptr =*temp++; //write data into FIFO
		Flag=Flag^0x01;//Flag for odd or even bytes
		if(CRCCONbits.CRCFUL==1)//check if FIFO is full
		{
			CRCCONbits.CRCGO=1; //start CRC engine
			while(CRCCONbits.CRCMPT!=1);//check if FIFO is empty
			CRCCONbits.CRCGO=0; //stop CRC engine
		}
	}
	
	if(CRCCONbits.CRCGO!=1)
	CRCCONbits.CRCGO=1;
	
	if(Flag==0) CRCDAT = 0x0000; //appending PLEN+1 zeros (multiply by 2^16)
	else *ptr=0x00;//appending (PLEN+1)/2 zeros (multiply by 2^8)
	
	while(CRCCONbits.CRCMPT!=1);//check if FIFO is empty
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	
	CRCCONbits.CRCGO=0; //stop CRC engine
	Nop();
	
	if(Flag==1) // if odd number of bytes,
	{ //append (PLEN+1)/2 zeros (multiply by 2^8)
		for(j = 0; j < 8; j ++)
		{
			Carry =( CRCWDAT & 0x8000);
			CRCWDAT <<= 1;
			if(Carry) CRCWDAT ^= 0x1021;
		}
	}
	return CRCWDAT;
}
