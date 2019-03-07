//#include "Rtcc.h"
#include "include\define.h"
extern unsigned char RxPacket[];
/*****************************************************************************
 * Structures: _time and _time_chk
 *
 * Overview: These structures contain the time and date.
 * RTCCProcessEvents updates them. _time_chk is used as input/output for
 * get/set operations.
 *
 *****************************************************************************/
RTCC _time;
RTCC _time_chk;
/*****************************************************************************
 * Arrays: _time_str and _date_str
 *
 * Overview: These arrays contain the time and date strings.
 * RTCCProcessEvents updates them.
 *
 *****************************************************************************/
char _time_str[5];
char _date_str[24];

// The flag stops updating time and date and used for get/set operations.
unsigned char _rtcc_flag;

/*****************************************************************************
 * Function: RTCCProcessEvents
 *
 * Preconditions: RTCCInit must be called before.
 *
 * Overview: The function grabs the current time from the RTCC and translate
 * it into strings.
 *
 * Input: None.
 *
 * Output: It update time and date strings  _time_str, _date_str,
 * and _time, _time_chk structures.
 *
 *****************************************************************************/
void RTCCProcessEvents(void) {
    // Process time object only if time is not being set
    while (!_rtcc_flag) {
        // Grab the time
        RCFGCALbits.RTCPTR = 0;
        _time.prt00 = RTCVAL;
        RCFGCALbits.RTCPTR = 1;
        _time.prt01 = RTCVAL;
        RCFGCALbits.RTCPTR = 2;
        _time.prt10 = RTCVAL;
        RCFGCALbits.RTCPTR = 3;
        _time.prt11 = RTCVAL;

        // Grab the time again
        RCFGCALbits.RTCPTR = 0;
        _time_chk.prt00 = RTCVAL;
        RCFGCALbits.RTCPTR = 1;
        _time_chk.prt01 = RTCVAL;
        RCFGCALbits.RTCPTR = 2;
        _time_chk.prt10 = RTCVAL;
        RCFGCALbits.RTCPTR = 3;
        _time_chk.prt11 = RTCVAL;

        // Verify there is no roll-over
        if ((_time.prt00 == _time_chk.prt00) &&
                (_time.prt01 == _time_chk.prt01) &&
                (_time.prt10 == _time_chk.prt10) &&
                (_time.prt11 == _time_chk.prt11)) {
            switch (_time.mth) {
                default:
                case 0x01: _date_str[5] = 'J';
                    _date_str[6] = 'a';
                    _date_str[7] = 'n';
                    break;
                case 0x02: _date_str[5] = 'F';
                    _date_str[6] = 'e';
                    _date_str[7] = 'b';
                    break;
                case 0x03: _date_str[5] = 'M';
                    _date_str[6] = 'a';
                    _date_str[7] = 'r';
                    break;
                case 0x04: _date_str[5] = 'A';
                    _date_str[6] = 'p';
                    _date_str[7] = 'r';
                    break;
                case 0x05: _date_str[5] = 'M';
                    _date_str[6] = 'a';
                    _date_str[7] = 'y';
                    break;
                case 0x06: _date_str[5] = 'J';
                    _date_str[6] = 'u';
                    _date_str[7] = 'n';
                    break;
                case 0x07: _date_str[5] = 'J';
                    _date_str[6] = 'u';
                    _date_str[7] = 'l';
                    break;
                case 0x08: _date_str[5] = 'A';
                    _date_str[6] = 'u';
                    _date_str[7] = 'g';
                    break;
                case 0x09: _date_str[5] = 'S';
                    _date_str[6] = 'e';
                    _date_str[7] = 'p';
                    break;
                case 0x10: _date_str[5] = 'O';
                    _date_str[6] = 'k';
                    _date_str[7] = 't';
                    break;
                case 0x11: _date_str[5] = 'N';
                    _date_str[6] = 'o';
                    _date_str[7] = 'v';
                    break;
                case 0x12: _date_str[5] = 'D';
                    _date_str[6] = 'e';
                    _date_str[7] = 'c';
                    break;
            }

            _date_str[4] = ' ';
            _date_str[11] = '.';
            _date_str[12] = ' ';
            _date_str[8] = ' ';
            _date_str[0] = '2';
            _date_str[1] = '0';

            _date_str[9] = (_time.day >> 4) + '0';
            _date_str[10] = (_time.day & 0xF) + '0';

            _date_str[2] = (_time.yr >> 4) + '0';
            _date_str[3] = (_time.yr & 0xF) + '0';

            _date_str[24] = 0;

            switch (_time.wkd) {
                default:
                case 0x00: _date_str[13] = 'V';
                    _date_str[14] = 'a';
                    _date_str[15] = 's';
                    _date_str[16] = 'a';
                    _date_str[17] = 'r';
                    _date_str[18] = 'n';
                    _date_str[19] = 'a';
                    _date_str[20] = 'p';
                    _date_str[21] = ' ';
                    break;
                case 0x01: _date_str[13] = 'H';
                    _date_str[14] = 'e';
                    _date_str[15] = 't';
                    _date_str[16] = 'f';
                    _date_str[17] = 'o';
                    _date_str[18] = ' ';
                    _date_str[19] = ' ';
                    _date_str[20] = ' ';
                    _date_str[21] = ' ';
                    break;
                case 0x02: _date_str[13] = 'K';
                    _date_str[14] = 'e';
                    _date_str[15] = 'd';
                    _date_str[16] = 'd';
                    _date_str[17] = ' ';
                    _date_str[18] = ' ';
                    _date_str[19] = ' ';
                    _date_str[20] = ' ';
                    _date_str[21] = ' ';
                    break;
                case 0x03: _date_str[13] = 'S';
                    _date_str[14] = 'z';
                    _date_str[15] = 'e';
                    _date_str[16] = 'r';
                    _date_str[17] = 'd';
                    _date_str[18] = 'a';
                    _date_str[19] = ' ';
                    _date_str[20] = ' ';
                    _date_str[21] = ' ';
                    break;
                case 0x04: _date_str[13] = 'C';
                    _date_str[14] = 's';
                    _date_str[15] = 'u';
                    _date_str[16] = 't';
                    _date_str[17] = 'o';
                    _date_str[18] = 'r';
                    _date_str[19] = 't';
                    _date_str[20] = 'o';
                    _date_str[21] = 'k';
                    break;
                case 0x05: _date_str[13] = 'P';
                    _date_str[14] = 'e';
                    _date_str[15] = 'n';
                    _date_str[16] = 't';
                    _date_str[17] = 'e';
                    _date_str[18] = 'k';
                    _date_str[19] = ' ';
                    _date_str[20] = ' ';
                    _date_str[21] = ' ';
                    break;
                case 0x06: _date_str[13] = 'S';
                    _date_str[14] = 'z';
                    _date_str[15] = 'o';
                    _date_str[16] = 'm';
                    _date_str[17] = 'b';
                    _date_str[18] = 'a';
                    _date_str[19] = 't';
                    _date_str[20] = ' ';
                    _date_str[21] = ' ';
                    break;
            }

            _time_str[0] = (_time.hr >> 4) + '0';
            _time_str[1] = (_time.hr & 0xF) + '0';
            _time_str[2] = ':';
            _time_str[3] = (_time.min >> 4) + '0';
            _time_str[4] = (_time.min & 0xF) + '0';

            //            _time_str[10] = (_time.sec >> 4) + '0';
            //          _time_str[11] = (_time.sec & 0xF) + '0';

            _time_str[5] = 0;

            break;
        }
    }
}

/*****************************************************************************
 * Function: RTCCInit
 *****************************************************************************/
void RTCCInit(void) {
    // Enables the LP OSC for RTCC operation
    asm("mov #OSCCON,W1");
    asm("mov.b  #0x02, W0");
    asm("mov.b  #0x46, W2");
    asm("mov.b  #0x57, W3");
    asm("mov.b  W2, [W1]");
    asm("mov.b  W3, [W1]");
    asm("mov.b  W0, [W1]");

    // Set the RTCC to a default value, and start it.
    RCFGCAL = 0x0000;
    RTCCUnlock();
    RCFGCALbits.RTCEN = 1;
    RTCCOn();
 //_time_chk.wkd = RxPacket[4];
    
    RTCCSetBinHour(RxPacket[3]);
    RTCCSetBinMin(RxPacket[2]);
    RTCCSetBinSec(RxPacket[1]);
    RTCCSetDay(RTCCBin2Dec(RxPacket[5])); //késõbb beállhoz ezt kell használni: RTCCSetBinDay(    RTCC_DEFAULT_DAY );
   // ellenõrzi hogy az adott hónapban van e annyi nap, de a honap és az év értékeknek a _time_chk.mth, _time_chk.yr-ben kell lenni
    RTCCSetBinMonth(RxPacket[6]);
    RTCCSetBinYear(RxPacket[7]);
    RTCCCalculateWeekDay();

    ALCFGRPTbits.AMASK = 3; //Set the alarm repeat to 	(3:every minute)
    ALCFGRPTbits.ALRMEN = 1; // alarm enable
    ALCFGRPTbits.CHIME = 1; // alarm repeat


    RTCCSet();
}

/*****************************************************************************
 * Function: RTCCSet
 *
 * Preconditions: None.
 *
 * Overview: The function upload time and date from _time_chk into clock.
 *
 * Input: _time_chk - structure containing time and date.
 *
 * Output: None.
 *
 *****************************************************************************/
void RTCCSet(void) {
    RTCCUnlock(); // Unlock the RTCC
    // Set the time
    RCFGCALbits.RTCPTR = 0;
    RTCVAL = _time_chk.prt00;
    RCFGCALbits.RTCPTR = 1;
    RTCVAL = _time_chk.prt01;
    RCFGCALbits.RTCPTR = 2;
    RTCVAL = _time_chk.prt10;
    RCFGCALbits.RTCPTR = 3;
    RTCVAL = _time_chk.prt11;
    RTCCLock(); // Lock the RTCC
    _rtcc_flag = 0; // Release the lock on the time
}

/*****************************************************************************
 * Function: RTCCUnlock
 *
 * Preconditions: None.
 *
 * Overview: The function allows a writing into the clock registers.
 *
 * Input: None.
 *
 * Output: None.
 *
 *****************************************************************************/
void RTCCUnlock(void) {
    asm volatile("disi  #5");
    asm volatile("mov   #0x55, w7");
    asm volatile("mov   w7, _NVMKEY");
    asm volatile("mov   #0xAA, w8");
    asm volatile("mov   w8, _NVMKEY");
    asm volatile("bset  _RCFGCAL, #13");
    asm volatile("nop");
    asm volatile("nop");
}

/*****************************************************************************
 * Function: RTCCSetBinSec
 *
 * Preconditions: None.
 *
 * Overview: The function verifies setting seconds range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Seconds binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinSec(unsigned char Sec) {
    if (Sec == 0xff) Sec = 59;
    if (Sec == 60) Sec = 0;
    RTCCSetSec(RTCCBin2Dec(Sec));
}

/*****************************************************************************
 * Function: RTCCSetBinMin
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting minutes range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Minutes binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinMin(unsigned char Min) {
    if (Min == 0xff) Min = 59;
    if (Min == 60) Min = 0;
    RTCCSetMin(RTCCBin2Dec(Min));
}

/*****************************************************************************
 * Function: RTCCSetBinHour
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting hours range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Hours binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinHour(unsigned char Hour) {
    if (Hour == 0xff) Hour = 23;
    if (Hour == 24) Hour = 0;
    RTCCSetHour(RTCCBin2Dec(Hour));
}

/*****************************************************************************
 * Function: RTCCCalculateWeekDay
 *
 * Preconditions: Valid values of day, month and year must be presented in
 * _time_chk structure.
 *
 * Overview: The function reads day, month and year from _time_chk and
 * calculates week day. Than It writes result into _time_chk. To write
 * the structure into clock RTCCSet must be called.
 *
 * Input: _time_chk with valid values of day, month and year.
 *
 * Output: Zero based week day in _time_chk structure.
 *
 *****************************************************************************/
void RTCCCalculateWeekDay() {
    const char MonthOffset[] =
            //jan feb mar apr may jun jul aug sep oct nov dec
    {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    unsigned Year;
    unsigned Month;
    unsigned Day;
    unsigned Offset;

    // calculate week day
    Year = RTCCGetBinYear();
    Month = RTCCGetBinMonth();
    Day = RTCCGetBinDay();

    // 2000s century offset = 6 +
    // every year 365%7 = 1 day shift +
    // every leap year adds 1 day
    Offset = 6 + Year + Year / 4;
    // Add month offset from table
    Offset += MonthOffset[Month - 1];
    // Add day
    Offset += Day;

    // If it's a leap year and before March there's no additional day yet
    if ((Year % 4) == 0)
        if (Month < 3)
            Offset -= 1;

    // Week day is
    Offset %= 7;

    RTCCSetWkDay(Offset);
}

/*****************************************************************************
 * Function: RTCCSetBinDay
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting day range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Day binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinDay(unsigned char Day) {
    const char MonthDaymax[] =
            //jan feb mar apr may jun jul aug sep oct nov dec
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned Daymax;
    unsigned Month;
    unsigned Year;

    Month = RTCCGetBinMonth();
    Year = RTCCGetBinYear();

    Daymax = MonthDaymax[Month - 1];

    // February has one day more for a leap year
    if (Month == 2)
        if ((Year % 4) == 0)
            Daymax++;

    if (Day == 0) Day = Daymax;
    if (Day > Daymax) Day = 1;
    RTCCSetDay(RTCCBin2Dec(Day));
}

/*****************************************************************************
 * Function: RTCCSetBinMonth
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting month range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Month binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinMonth(unsigned char Month) {
    if (Month < 1) Month = 12;
    if (Month > 12) Month = 1;
    RTCCSetMonth(RTCCBin2Dec(Month));
}

/*****************************************************************************
 * Function: RTCCSetBinYear
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting year range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Year binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinYear(unsigned char Year) {
    if (Year == 0xff) Year = 99;
    if (Year == 100) Year = 0;
    RTCCSetYear(RTCCBin2Dec(Year));

    // Recheck day. Leap year influences to Feb 28/29.
    RTCCSetBinDay(RTCCGetBinDay());
}
