#include "GetTime.h"

//=========================
// 🔹 RTC Object
//=========================
RTC_DS3231 rtc;
bool rtcInitialized = false;

//=========================
// 🔹 Initialize RTC
//=========================
void initializeRTC() {
  Serial.println(F("Initializing DS3231 RTC..."));
  
  if (!rtc.begin()) {
    Serial.println(F("❌ Couldn't find RTC!"));
    Serial.println(F("Check wiring: SDA->D2, SCL->D1"));
    rtcInitialized = false;
    return;
  }
  
  Serial.println(F("✅ RTC found!"));
  
  // Check if RTC lost power (battery dead)
  if (rtc.lostPower()) {
    Serial.println(F("⚠️ RTC lost power, setting time..."));
    // Set to compile time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Disable 32kHz output (save power)
  rtc.disable32K();
  
  // Get current time to verify
  DateTime now = rtc.now();
  Serial.print(F("Current RTC Time: "));
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  
  // Get temperature from RTC chip
  float temp = rtc.getTemperature();
  Serial.print(F("RTC Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C"));
  
  rtcInitialized = true;
}

//=========================
// 🔹 Update Time Display (Non-Blocking)
//=========================
void updateTimeDisplay() {
  if (!rtcInitialized) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10, 28);
    display.println(F("RTC Not Found!"));
    display.display();
    return;
  }
  
  DateTime now = rtc.now();
  
  display.clearDisplay();
  
  // ===== Date Display (Top) =====
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  // Day of week
  const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  display.print(daysOfWeek[now.dayOfTheWeek()]);
  display.print(", ");
  
  // Date (DD/MM/YYYY)
  if (now.day() < 10) display.print('0');
  display.print(now.day());
  display.print('/');
  if (now.month() < 10) display.print('0');
  display.print(now.month());
  display.print('/');
  display.println(now.year());
  
  // ===== Time Display (Large, Center) =====
  display.setTextSize(3);
  display.setCursor(10, 20);
  
  // Hour (24-hour format)
  if (now.hour() < 10) display.print('0');
  display.print(now.hour());
  
  // Blinking colon effect (blink every second)
  if (now.second() % 2 == 0) {
    display.print(':');
  } else {
    display.print(' ');
  }
  
  // Minute
  if (now.minute() < 10) display.print('0');
  display.println(now.minute());
  
  // ===== Seconds Display (Small, Below) =====
  display.setTextSize(2);
  display.setCursor(50, 50);
  if (now.second() < 10) display.print('0');
  display.print(now.second());
  
  display.display();
}

//=========================
// 🔹 Manually Set RTC Time
//=========================
void setRTCTime(int year, int month, int day, int hour, int minute, int second) {
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
  Serial.println(F("✅ RTC time updated!"));
}
