#ifndef GETTIME_H
#define GETTIME_H

#include "TionBot.h"
#include <RTClib.h>

//=========================
// 🔹 RTC Object
//=========================
extern RTC_DS3231 rtc;

//=========================
// 🔹 Time Display Variables
//=========================
extern bool rtcInitialized;

//=========================
// 🔹 Function Declarations
//=========================
void initializeRTC();
void updateTimeDisplay();
void setRTCTime(int year, int month, int day, int hour, int minute, int second);

#endif
