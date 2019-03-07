
//#include <p24Fxxxx.h>

// PIC24F16KA102 Configuration Bit Settings

int FBS __attribute__((space(prog), address(0xF80000))) = 0xF;
//_FBS(
//    BWRP_OFF &           // Table Write Protect Boot (Boot segment may be written)
//    BSS_OFF              // Boot segment Protect (No boot program Flash segment)
//);
int FGS __attribute__((space(prog), address(0xF80004))) = 0x3;
//_FGS(
//    GWRP_OFF &           // General Segment Code Flash Write Protection bit (General segment may be written)
//    GCP_OFF              // General Segment Code Flash Code Protection bit (No protection)
//);
int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0x87;
//_FOSCSEL(
//    FNOSC_FRCDIV &       // Oscillator Select (8 MHz FRC oscillator with divide-by-N (FRCDIV))
//    IESO_ON              // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-Speed Start-up enabled))
//);
int FOSC __attribute__((space(prog), address(0xF80008))) = 0xDB;
//_FOSC(
//    POSCMOD_NONE &       // Primary Oscillator Configuration bits (Primary oscillator disabled)
//    OSCIOFNC_ON &        // CLKO Enable Configuration bit (CLKO output disabled; pin functions as port I/O)
//    POSCFREQ_HS &        // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
//    SOSCSEL_SOSCLP &     // SOSC Power Selection Configuration bits (Secondary oscillator configured for low-power operation)
//    FCKSM_CSDCMD         // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)
//);
int FWDT __attribute__((space(prog), address(0xF8000A))) = 0x5F;
//_FWDT(
//    WDTPS_PS32768 &      // Watchdog Timer Postscale Select bits (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (WDT prescaler ratio of 1:128)
//    WINDIS_OFF &         // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
//    FWDTEN_OFF           // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
//);
int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFB;
//_FPOR(
//    BOREN_BOR3 &         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
//    PWRTEN_ON &          // Power-up Timer Enable bit (PWRT enabled)
//    I2C1SEL_PRI &        // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
//    BORV_V18 &           // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
//    MCLRE_ON             // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)
//);
int FICD __attribute__((space(prog), address(0xF8000E))) = 0xC3;
//_FICD(
//    ICS_PGx1             // ICD Pin Placement Select bits (PGC1/PGD1 are used for programming and debugging the device)
//);
int FDS __attribute__((space(prog), address(0xF80010))) = 0xFF;
//_FDS(
//    DSWDTPS_DSWDTPSF &   // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
//    DSWDTOSC_LPRC &      // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
//    RTCOSC_SOSC &        // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
//    DSBOREN_ON &         // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
//    DSWDTEN_ON           // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)
//);

#include "include\define.h"
int key;
long int temp, humi;
char Ta[11] = "00.0C   00%";
char join[12] = "csatlakozas";

// rf input/output buffers:
extern unsigned char RxPacket[]; // Receive data puffer (payload only)
extern unsigned char TxPacket[]; // Transmit data puffer
extern unsigned char RxPacketLen;
extern BOOL hasPacket;
extern WORD rcrc, ccrc;
BOOL kuld;
unsigned char mp;

// Set Date/Time Variables

SHORT currentControlSet;
BYTE daysPerMonth[12] = {31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};

/*XCHAR monthNames[12][3] = {
    { 'J', 'a', 'n',},
    { 'F', 'e', 'b',},
    { 'M', 'a', 'r',},
    { 'A', 'p', 'r',},
    { 'M', 'a', 'y',},
    { 'J', 'u', 'n',},
    { 'J', 'u', 'l',},
    { 'A', 'u', 'g',},
    { 'S', 'e', 'p',},
    { 'O', 'c', 't',},
    { 'N', 'o', 'v',},
    { 'D', 'e', 'c'}
};*/

///////////////////////////////// FONTS ///////////////////////////////////////
extern const FONT_FLASH Font29pix; //GenBasB_1;
extern const FONT_FLASH Font53pix; //GenBasB_2;
extern const FONT_FLASH Font13pix;


// SHT linearization constants
const unsigned int C1 = 400; // -4
const unsigned int C2 = 405; // 0.0405  (405 * 10^-4)
const unsigned short C3 = 28; // -2.8 * 10^-6  (28 * 10^-7)
const unsigned int D1 = 4000; // -40
const unsigned short D2 = 1; // 0.01



//*************************************************************************************
//
//		Init
//
//*************************************************************************************

void init(void) {
    AD1PCFG = 0b1111111111111111; // AD port config register 1 -> port is dig. I/O; 0 -> analog input

    A0_TRIS_BIT = 0; //TRISAbits.TRISA3 (LCD A0)
    RST_TRIS_BIT = 0;
    RST_LAT_BIT = 0;
    CS_TRIS_BIT = 0;
    CS_LAT_BIT = 1;

    BUZZER = 0; //PIEZO
    BUZZER_TRIS = 0;

    LED = 0; //LED
    LED_TRIS = 0;

    HP03_XCLR = 0; //HP03 XCLR
    HP03_XCLR_TRIS = 0;

    // RF =====================
    TRISBbits.TRISB2 = 0; // NSEL        	PORTBbits.RB2                              // chip select, active low output
    TRISAbits.TRISA7 = 0; // NFFS        	PORTAbits.RA7                              // rx fifo select, active low output
    TRISAbits.TRISA6 = 1; // NIRQ			PORTAbits.RA6
    //LATAbits.LATA6=0;
    NSEL = 1; // nSEL inactive
    NFFS = 1; // nFFS inactive

    //PADCFG1bits.OC1TRIS=1; //RA6?

    CNPU1bits.CN12PUE = 1; //RB14	key input
    LATBbits.LATB0 = 1; //csak így mûködik a pullup-os bemenet...?

    CNEN1bits.CN12IE = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

    INTCON2bits.INT2EP = 1; // INT2 lefutó él

    CNPD1 = 0; // pulldowns disable
    CNPD2 = 0; // pulldowns disable

    //================= SPI setup ======================================

    SPI1CON1 = 0b0000000100111111; // SMP:0, CKP:0, CKE:1, 8bit mode
    SPI1CON2 = 0b0000000000000000; //enhanced buffer mode disable
    SPI1STATbits.SPIEN = 1; /* Enable/Disable the spi module */

    /************************ IIC setup ****************************/

    /* clear the I2CEN bit */
    I2C1CONbits.I2CEN = 0;

    /* clear the SI2C & MI2C Interrupt enable bits */
    IEC1bits.SI2C1IE = 0;
    IEC1bits.MI2C1IE = 0;

    /* clear the SI2C & MI2C Interrupt flag bits */
    IFS1bits.SI2C1IF = 0;
    IFS1bits.MI2C1IF = 0;

    IEC3bits.RTCIE = 1;

    I2C1BRG = 200; //39
    // I2C1CON = 0b1000001000000000; //I2C1 enabled, slew rate control disabled

    REFOCON = 0b0000011100000000; //Reference Oscillator Output disabled; ref osc divisor Base clock value divided by 128 (HP03 MCLK)
    ODCBbits.ODB8 = 1; //open drain control bit
    ODCBbits.ODB9 = 1;
    SCLdir = 0;

}

//*************************************************************************
//
// Int on change interrupt
//
//*************************************************************************

void __attribute__((interrupt, shadow, auto_psv)) _CNInterrupt(void) {
    key = 0;
    if (!PORTBbits.RB0) key += 1;
    if (!PORTBbits.RB1) key += 2;
    if (!PORTBbits.RB14) {
        key += 4;
        kuld = TRUE;
    }
    IFS1bits.CNIF = 0;
}

//*************************************************************************
//
// RTCC interrupt
//
//*************************************************************************

void __attribute__((interrupt, shadow, auto_psv)) _RTCCInterrupt(void) {
    IFS3bits.RTCIF = 0;
}

//************************************************************************
//
//	Main
//
//************************************************************************

int main(void) {

    int i, x;
    union int_char tempraw, humiraw;
    long int temp, humi, tmp;

    init();
    InitGraph(); // RESET-eli az RF modult is a közös RESET vonalon keresztül!!!!!!!!!!!!!!!!!!!!!!!!
    RF_init();

   // x = RF_join();

/*    Ta[0] = x % 1000 / 100 + 48; // example: Ta[6] = 12345 % 10000 = 2345, Ta[6] = 2345 / 1000 = 2, 2 + 48 = '2' - ASCII
    Ta[1] = x % 100 / 10 + 48; // example: Ta[7] = 12345 % 1000 = 345, Ta[7] = 345 / 100 = 3, 3 + 48 = '3' - ASCII
    Ta[2] = x % 10 + 48;
    Ta[3]='!';
    Ta[4] = RxPacket[0] % 1000 / 100 + 48; // example: Ta[6] = 12345 % 10000 = 2345, Ta[6] = 2345 / 1000 = 2, 2 + 48 = '2' - ASCII
    Ta[5] = RxPacket[0] % 100 / 10 + 48; // example: Ta[7] = 12345 % 1000 = 345, Ta[7] = 345 / 100 = 3, 3 + 48 = '3' - ASCII
    Ta[6] = RxPacket[0] % 10 + 48;
    Ta[7]='!';

    
    OutTextXY(10, 30, Ta); //41
    TransferToLCD();
    ClearDevice();
*/
    //while(1);

    RTCCInit();
    RTCCProcessEvents();

    TxPacket[0] = HELYISEG + '0'; //      module id
    TxPacket[1] = 0x2c; //,
    TxPacket[7] = 0x2c;
    TxPacket[12] = 0x2c;

    _date_str[22] = TxPacket[0]; // module id


    while (1) {

        key = 0;

        RTCCProcessEvents();

        x = GetTextWidth(&_time_str, &Font53pix);
        SetFont((void *) &Font53pix); //53
        OutTextXY((128 - x) >> 1, -12, _time_str);

        SetFont((void *) &Font13pix);
        x = GetTextWidth(&_date_str, &Font13pix);
        OutTextXY((128 - x) >> 1, 29, _date_str); //5

        for (i = 0; i < 128; i++) {
            PutPixel(i, 45); //44,42
            PutPixel(i, 43);
        }

        SHT_measure(&tempraw.char_[1], &tempraw.char_[0], &humiraw.char_[1], &humiraw.char_[0]); //lásd.:http://www.eet.bme.hu/~czirkos/referenciak.php

        // Calculating temperature Ta_res = D1 + D2 * SOt
        if (tempraw.int_ > D1) // if temperature is positive
            temp = tempraw.int_ * D2 - D1; // calculate temperature
        else // else (if temperature is negative)
            temp = D1 - tempraw.int_ * D2; // calculate temperature

        // Calculating humidity
        tmp = humiraw.int_ * humiraw.int_ * C3 / 100000; // Rh_res = C1 + C2 * SOrh + C3 * SOrh^2
        humi = humiraw.int_ * C2 / 100 - tmp - C1; // calculate humidity

        Ta[0] = temp % 10000 / 1000 + 48; // example: Ta[6] = 12345 % 10000 = 2345, Ta[6] = 2345 / 1000 = 2, 2 + 48 = '2' - ASCII
        Ta[1] = temp % 1000 / 100 + 48; // example: Ta[7] = 12345 % 1000 = 345, Ta[7] = 345 / 100 = 3, 3 + 48 = '3' - ASCII
        Ta[3] = temp % 100 / 10 + 48; // example: Ta[9] = 12345 % 100 = 45, Ta[9] = 45 / 10 = 4, 4 + 48 = '4' - ASCII

        Ta[8] = humi % 10000 / 1000 + 48; // example: Rh[6] = 12345 % 10000 = 2345, Rh[6] = 2345 / 1000 = 2, 2 + 48 = '2' - ASCII
        Ta[9] = humi % 1000 / 100 + 48; // example: Rh[7] = 12345 % 1000 = 345, Rh[7] = 345 / 100 = 3, 3 + 48 = '3' - ASCII

        SetFont((void *) &Font29pix); //29
        OutTextXY(3, 42, Ta); //41

        TransferToLCD();
        ClearDevice();

        TxPacket[2] = tempraw.char_[1]; //_time_str[0];
        TxPacket[3] = tempraw.char_[0]; //_time_str[1];
        TxPacket[4] = humiraw.char_[1]; //_time_str[2];
        TxPacket[5] = humiraw.char_[0]; //_time_str[3];
        //TxPacket[6] = _time_str[4];
        //TxPacket[7] = ',';
        //TxPacket[8] = Ta[0];
        //TxPacket[9] = Ta[1];
        //TxPacket[10] = '.';
        //TxPacket[11] = Ta[3];
        //TxPacket[12] = ',';
        //TxPacket[13] = Ta[8];
        //TxPacket[14] = Ta[9];
        //TxPacket[15] = '%';

        Tx(5);

        mPWRMGNT_GotoSleepMode();

        if (PwrMgnt_WakeupSource() == WAKEUP_SLEEP) LED = 0;
    }
}
