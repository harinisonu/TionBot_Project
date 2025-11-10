#ifndef WEATHER_H
#define WEATHER_H
#include "TionBot.h"
#include "Emotes.h"

#define XPOS   0 // Indexes into the 'icons' array
#define YPOS   1
#define DELTAY 2

//=========================
// 🔹 OLED setup - weather
//=========================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUMDROPS     10 // Number of Rain Drops

#define LOGO_HEIGHT   16   // height of raindrop bitmap
#define LOGO_WIDTH    16   // width of raindrop bitmap (or just 2 px line)
#define SCREEN_HEIGHT 64

//=========================
// 🔹 OpenWeatherMap setup
//=========================
extern const char* city;
extern const char* apiKey;
extern float temperature;
extern int humidity;
extern String weather;
extern String description;
extern bool weatherDataReady; 
extern const unsigned char PROGMEM dropLet[];
extern const uint8_t PROGMEM icon_sun_16[];
extern const uint8_t PROGMEM icon_mist_16[];
extern const uint8_t PROGMEM icon_drizzle_16[];
extern const uint8_t PROGMEM icon_clouds_16[];
extern const uint8_t PROGMEM icon_thunder_16[];
extern const uint8_t PROGMEM icon_unknown_16[];

// Implement weather API fetch
void connectToWiFi();
void fetchWeatherData(); 

#endif
