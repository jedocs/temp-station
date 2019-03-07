
#ifndef _RTCC_H_
#define _RTCC_H_

#define	EECON2	NVMKEY 

// Setup clock
extern void RTCCInit(void);
// Must be called periodically to refresh time and date strings
extern void RTCCProcessEvents(void);
// Write changed time and date to clock registers 
extern void RTCCSet(void);
// Unlock access to clock and read time and date 
extern void RTCCUnlock(void);

// Union to access rtcc registers
typedef union tagRTCC {
	struct {
		unsigned char sec;
		unsigned char min;
		unsigned char hr;
		unsigned char wkd;
		unsigned char day;
		unsigned char mth;
		unsigned char yr;
	};
	struct {
		unsigned int prt00;
		unsigned int prt01;
		unsigned int prt10;
		unsigned int prt11;
	};
} RTCC;

// Gets time and date 
extern RTCC _time;
// Gets time and date second time to detect overflow
extern RTCC _time_chk;
// Prevents updating of _time and _time_chk
extern unsigned char _rtcc_flag;
// _time_str and _date_str contain current time and date strings
extern char _time_str[5]; // Sat 10:01:15
extern char _date_str[24]; // Sep 30, 2005

// Macroses to initiate and set RTCC
#define RTCCOn()		RCFGCALbits.RTCEN = 1;
#define	RTCCOff()		RCFGCALbits.RTCEN = 0;
#define RTCCLock()		RCFGCALbits.RTCWREN = 0;

#define RTCCGetSec()	_time_chk.sec
#define RTCCGetMin()	_time_chk.min
#define RTCCGetHour()	_time_chk.hr
#define RTCCGetWkDay()	_time_chk.wkd
#define RTCCGetDay()	_time_chk.day
#define RTCCGetMonth()	_time_chk.mth
#define	RTCCGetYear()	_time_chk.yr

#define RTCCSetSec(__rtccdat)		_time_chk.sec = __rtccdat; _rtcc_flag = 1;
#define RTCCSetMin(__rtccdat)		_time_chk.min = __rtccdat; _rtcc_flag = 1;
#define RTCCSetHour(__rtccdat)		_time_chk.hr = __rtccdat; _rtcc_flag = 1;
#define RTCCSetWkDay(__rtccdat)	    _time_chk.wkd = __rtccdat; _rtcc_flag = 1;
#define RTCCSetDay(__rtccdat)		_time_chk.day = __rtccdat; _rtcc_flag = 1;
#define RTCCSetMonth(__rtccdat)	    _time_chk.mth = __rtccdat; _rtcc_flag = 1;
#define	RTCCSetYear(__rtccdat)		_time_chk.yr = __rtccdat; _rtcc_flag = 1;

// Macroses and functions to get/verify and set time and date
extern void RTCCSetBinSec(unsigned char Sec);
extern void RTCCSetBinMin(unsigned char Min);
extern void RTCCSetBinHour(unsigned char Hour);
extern void RTCCSetBinDay(unsigned char Day);
#define     RTCCSetBinWkDay(x)  RTCCSetWkDay(x)
extern void RTCCSetBinMonth(unsigned char Month);
// Set a new year value and correct Feb 29 for none leap year
extern void RTCCSetBinYear(unsigned char Year);
// Reads current year, month, day, calculates and set week day 
extern void RTCCCalculateWeekDay();

#define RTCCDec2Bin(Dec)    (10*(Dec>>4)+(Dec&0x0f))
#define RTCCBin2Dec(Bin)    (((Bin/10)<<4)|(Bin%10))
#define RTCCGetBinSec()      RTCCDec2Bin(RTCCGetSec())
#define RTCCGetBinMin()      RTCCDec2Bin(RTCCGetMin())
#define RTCCGetBinHour()     RTCCDec2Bin(RTCCGetHour())
#define RTCCGetBinWkDay()    RTCCDec2Bin(RTCCGetWkDay())
#define RTCCGetBinDay()      RTCCDec2Bin(RTCCGetDay())
#define RTCCGetBinMonth()    RTCCDec2Bin(RTCCGetMonth())
#define RTCCGetBinYear()     RTCCDec2Bin(RTCCGetYear())
/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif
