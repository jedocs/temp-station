
#include <p24Fxxxx.h>
//#include <stdlib.h>

#include "PwrMgnt.h"
#include "Rtcc.h"
#include "include/primitive.h"



#define HELYISEG 2  // halo:1, peti:2, edina:3, nappali:4, kulso:5
#define GetSystemClock()    (32000000ul)
#define GetPeripheralClock()    (GetSystemClock() / 2)
#define GetInstructionClock()   (GetSystemClock() / 2)

typedef unsigned char BYTE; // 8-bit unsigned
typedef unsigned short int WORD; // 16-bit unsigned
//typedef unsigned long		DWORD;
typedef signed short int SHORT; // 16-bit signed
typedef void VOID;
typedef signed int INT;
typedef signed char INT8;
typedef signed short int INT16;
typedef signed long int INT32;
typedef signed long long INT64;

typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned long int UINT32; // other name for 32-bit integer
typedef unsigned long long UINT64;

typedef enum _BOOL {
    FALSE = 0, TRUE
} BOOL; /* Undefined size */

#define USE_FONT_FLASH

#define USE_AND_OR /* To enable AND_OR mask setting */

//********************** LCD interface ***************************
#define RST_TRIS_BIT    TRISBbits.TRISB6
#define RST_LAT_BIT     LATBbits.LATB6

// Definitions for CS pin
#define CS_TRIS_BIT TRISBbits.TRISB5
#define CS_LAT_BIT  LATBbits.LATB5

// Definitions for A0 line
#define A0_LAT_BIT  LATAbits.LATA3
#define A0_TRIS_BIT TRISAbits.TRISA3

typedef enum {
    FLASH = 0, // internal flash
    EXTERNAL = 1, // external memory
    RAM = 2, // RAM
    VIDEOBUF = 3 // video buffer
} TYPE_MEMORY;

typedef struct {
    TYPE_MEMORY type; // must be FLASH
    const char *address; // font image address
} FONT_FLASH;

#ifdef USE_MULTIBYTECHAR
#define XCHAR   short
#else
#define XCHAR   char
#endif

#define ORIENT_HOR  0
#define ORIENT_VER  1

#define MoveTo(x, y) \
    _cursorX = x;        \
    _cursorY = y;

//****************************************************************

#define LED_TRIS 	TRISAbits.TRISA1
#define BUZZER_TRIS 	TRISBbits.TRISB12
#define LED 		LATAbits.LATA1
#define BUZZER 		LATBbits.LATB12
#define HP03_XCLR 	LATAbits.LATA2
#define HP03_XCLR_TRIS 	TRISAbits.TRISA1

//******************* RF
#define FREQ_Band       0x0020                                 //868MHz
#define FREQ_start      710
#define FREQ_step       90
#define FREQ_maxid      13
#define MAX_FREQ        "13"
#define RF_DEV      	90

#define SDOdir          TRISBbits.TRISB13
#define SCKdir          TRISBbits.TRISB11
#define SDIdir          TRISBbits.TRISB10

#define SPI_SDO         LATBbits.LATB13
#define SPI_SCK         LATBbits.LATB11
#define SPI_SDI         PORTBbits.RB10
#define NSEL            PORTBbits.RB2                              // chip select, active low output
#define NFFS            PORTAbits.RA7                              // rx fifo select, active low output
#define NIRQ		PORTAbits.RA6	 
#define FFIT		PORTBbits.RB7

// Application constants:

#define PAYLOAD_LEN 20                                         // TX (RX) payload size
#define PACKET_LEN  PAYLOAD_LEN + 4                            // TX (RX) packet size ([AAAA]AA2DD4 + PL + payload)
#define TXBUF_LEN   PACKET_LEN + 2                             // TX buffer size (TX packet + 2 bytes dummy)

// Define the RTCC default initialization.
#define RTCC_DEFAULT_DAY        12		//jan 25 volt
#define RTCC_DEFAULT_MONTH      11
#define RTCC_DEFAULT_YEAR       13        // 2013
//#define RTCC_DEFAULT_WEEKDAY    07        // sun ?????????
#define RTCC_DEFAULT_HOUR       21
#define RTCC_DEFAULT_MINUTE     10
#define RTCC_DEFAULT_SECOND     01


//*************************** SHT

#define	SDA 	PORTBbits.RB9
#define SDAdir	TRISBbits.TRISB9
#define	SCL   	LATBbits.LATB8
#define SCLdir	TRISBbits.TRISB8

#define OUT		0
#define IN		1
#define noACK 0
#define ACK   1

#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0

void Delay10us(UINT32 tenMicroSecondCounter);
void DelayMs(UINT16 ms);

union int_char {
    int int_;
    char char_ [2];
};
