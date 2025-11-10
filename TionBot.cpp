#include "TionBot.h"

//=========================
// 🔹 WiFi credentials
//=========================a
const char* ssid = "Rajashree";
const char* password = "9940356774";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String voiceCommand = "";
