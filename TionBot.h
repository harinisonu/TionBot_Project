#ifndef TIONBOT_H
#define TIONBOT_H

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <RTClib.h> 

//=========================
// 🔹 Blynk Credentials
//=========================
#define BLYNK_TEMPLATE_ID "TMPL39aQPt60Q"
#define BLYNK_TEMPLATE_NAME "Voice Tion"
#define BLYNK_AUTH_TOKEN "cKOd4bYWuvpe5yIhmHku3nWWbN8g7Hj0"

//=========================
// 🔹 WiFi Credentials
//=========================
extern const char* ssid;
extern const char* password;

//=========================
// 🔹 OLED Setup
//=========================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 0
extern Adafruit_SSD1306 display;

//=========================
// 🔹 Voice Command
//=========================
extern String voiceCommand;

//=========================
// 🔹 Function Declarations
//=========================
void connectToWiFi();

#endif
