#include "include/define.h"
//#include "include/primitive.h"
#define NULL 0;

// Font orientation
BYTE _fontOrientation;

// Current cursor x-coordinates
SHORT _cursorX;

// Current cursor y-coordinates
SHORT _cursorY;

// Pointer to the current font
void *_font;


unsigned char VMap[1024];


// First and last characters in the font
WORD _fontFirstChar; // First character in the font table.
WORD _fontLastChar; // Last character in the font table.

// Installed font height
SHORT _fontHeight;


WORD OutChar(XCHAR);

/*********************************************************************
 * Function:  void ResetDevice()
 ********************************************************************/
void ResetDevice(void) {
    
    RST_LAT_BIT = 1;
    DelayMs(2);

    A0_LAT_BIT = 0;
    CS_LAT_BIT = 0;

    SPIPut(0x40); //(2) Display start line set 0 0 1 0 0 0 0 0 0 $40 Display start line 0
    SPIPut(0xA0); //(8) ADC set 0 1 0 1 0 0 0 0 0 $A0 ADC normal
    SPIPut(0xC8); //(15) Common output mode select 0 1 1 0 0 1 0 0 0 $C8 reverse COM63~COM0
    SPIPut(0xA6); //(9) Display normal/reverse 0 1 0 1 0 0 1 1 0 $A6 Display normal
    SPIPut(0xA2); //(11) LCD bias set 0 1 0 1 0 0 0 1 0 $A2 Set bias 1/9 (Duty 1/65)
    SPIPut(0x2F); //(16) Power control set 0 0 0 1 0 1 1 1 1 $2F Booster, Regulator and Follower on
    SPIPut(0xF8); //(20) Booster ratio set 0 1 1 1 1 1 0 0 0 $F8 Set internal Booster to 4x
    SPIPut(0x00); //0 0 0 0 0 0 0 0 $00
    SPIPut(0x27); //(17) V0 voltage regulator set 0 0 0 1 0 0 1 1 1 $27
    SPIPut(0x81); //(18) Electronic volume mode set 0 1 0 0 0 0 0 0 1 $81 Contrast set
    SPIPut(0x10); //0 0 0 1 0 1 1 0 $10
    SPIPut(0xAC); //(19) Static indicator set 0 1 0 1 0 1 1 0 0 $AC No indicator
    SPIPut(0x00); //0 0 0 0 0 0 0 0 $00
    SPIPut(0xAF); //(1) Display ON/OFF 0 1 0 1 0 1 1 1 1 $AF Display on

    //a5: all pixels on, a7:reverse display, a6:normal display

    CS_LAT_BIT = 1;
}

//*********************************************************

void ClearDevice(void) {
    int i;
    for (i = 0; i < 1024; i++) VMap[i] = 0x00;
}

//**********************************************************

void TransferToLCD(void) {
    unsigned char y, x;

    CS_LAT_BIT = 0;

    for (y = 0; y < 8; y++) {
        A0_LAT_BIT = 0;
        SPIPut(0xB0 + y); // set bank
        SPIPut(0x10); //set column
        SPIPut(0x04); //set column 4
        A0_LAT_BIT = 1;

        for (x = 0; x < 128; x++) {
            SPIPut(VMap[(y << 7) + x]);
        }
    }

    CS_LAT_BIT = 1;
}

/*********************************************************************
 * Function: void PutPixel(signed short int x, signed short int y)
 *
 ********************************************************************/
void PutPixel(unsigned short int x, unsigned short int y) {
    VMap[((y >> 3) << 7) + x] |= (1 << (y & 7));
}

/*********************************************************************
 * Function: WORD GetPixel(signed short int x, signed short int y)
 *
 ********************************************************************/
unsigned char GetPixel(signed short int x, signed short int y) {
    return (VMap[((y >> 3) << 7) + x] & (1 << (y & 7)));
}

/*********************************************************************
 * Function:  void InitGraph(void) 
 ********************************************************************/
void InitGraph(void) {

    MoveTo(0, 0); // Current cursor coordinates to 0,0
    ResetDevice();
    ClearDevice();
}

/*********************************************************************
 * Function: void SetFont(void* font)
 *
 * Input: pointer to the font image 
 ********************************************************************/
void SetFont(void *font) {

    FONT_HEADER *pHeader;
    _font = font;
    switch (*((SHORT *) font)) {
        case FLASH:
            pHeader = (FONT_HEADER *) ((FONT_FLASH *) font)->address;
            break;
        default:
            return;
    }

    _fontFirstChar = pHeader->firstChar;
    _fontLastChar = pHeader->lastChar;
    _fontHeight = pHeader->height;
}

/*********************************************************************
 * Function: WORD OutTextXY(SHORT x, SHORT y, XCHAR* textString)
 * Input: x,y - starting coordinates, textString - pointer to text string
 * Output: non-zero if drawing done (used for NON-BLOCKING configuration)
 ********************************************************************/
WORD OutTextXY(SHORT x, SHORT y, XCHAR *textString) {
    XCHAR ch;

    MoveTo(x, y);
    while ((XCHAR) 15 < (XCHAR) (ch = *textString++))
        while (OutChar(ch) == 0);
    return (1);
}

/*********************************************************************
 * Function: WORD OutChar(XCHAR ch)
 ********************************************************************/

WORD OutChar(XCHAR ch) {
    GLYPH_ENTRY *pChTable = NULL;
    BYTE *pChImage = NULL;

    SHORT chWidth = 0;
    SHORT xCnt, yCnt, x = 0, y;
    BYTE temp = 0, mask;

    if ((XCHAR) ch < (XCHAR) _fontFirstChar)
        return (-1);
    if ((XCHAR) ch > (XCHAR) _fontLastChar)
        return (-1);

    switch (*((SHORT *) _font)) {

        case FLASH:
            pChTable = (GLYPH_ENTRY *) (((FONT_FLASH *) _font)->address + sizeof (FONT_HEADER)) + ((XCHAR) ch - (XCHAR) _fontFirstChar);

            pChImage = (BYTE *) (((FONT_FLASH *) _font)->address + ((unsigned long) (pChTable->offsetMSB) << 8) + pChTable->offsetLSB);

            chWidth = pChTable->width;

            break;

        default:
            break;
    }

    if (_fontOrientation == ORIENT_HOR) {
        y = GetY();
        for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
            x = GetX();
            mask = 0;
            for (xCnt = 0; xCnt < chWidth; xCnt++) {
                if (mask == 0) {
                    temp = *pChImage++;
                    mask = 0x01;
                }

                if (temp & mask) {
                    PutPixel(x, y);
                }

                x++;
                mask <<= 1;
            }

            y++;
        }

        // move cursor
        _cursorX = x;
    } else {
        y = GetX();
        for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
            x = GetY();
            mask = 0;
            for (xCnt = 0; xCnt < chWidth; xCnt++) {
                if (mask == 0) {
                    temp = *pChImage++;
                    mask = 0x01;
                }

                if (temp & mask) {
                    PutPixel(y, x);
                }

                x--;
                mask <<= 1;
            }

            y++;
        }

        // move cursor
        _cursorY = x;
    }

    return (1);
}

/*********************************************************************
 * Function: SHORT GetTextWidth(XCHAR* textString, void* font)
 * Input: textString - pointer to the text string,
 *        font - pointer to the font
 *
 * Output: text width in pixels
 ********************************************************************/
SHORT GetTextWidth(XCHAR *textString, void *font) {
    GLYPH_ENTRY *pChTable;
    FONT_HEADER *pHeader;

    SHORT textWidth;
    XCHAR ch;
    XCHAR fontFirstChar;
    XCHAR fontLastChar;

    switch (*((SHORT *) font)) {

        case FLASH:
            pHeader = (FONT_HEADER *) ((FONT_FLASH *) font)->address;
            fontFirstChar = pHeader->firstChar;
            fontLastChar = pHeader->lastChar;
            pChTable = (GLYPH_ENTRY *) (pHeader + 1);
            textWidth = 0;
            while ((XCHAR) 15 < (XCHAR) (ch = *textString++)) {
                if ((XCHAR) ch < (XCHAR) fontFirstChar)
                    continue;
                if ((XCHAR) ch > (XCHAR) fontLastChar)
                    continue;
                textWidth += (pChTable + ((XCHAR) ch - (XCHAR) fontFirstChar))->width;
            }

            return (textWidth);

        default:
            return (0);
    }
}

/*********************************************************************
 * Function: SHORT GetTextHeight(void* font)
 * Output: character height in pixels
 * Overview: returns characters height for the font
 ********************************************************************/
SHORT GetTextHeight(void *font) {
    switch (*((SHORT *) font)) {
        case FLASH:
            return ((FONT_HEADER *) ((FONT_FLASH *) font)->address)->height;

        default:
            return (0);
    }
}

