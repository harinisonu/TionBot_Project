#include "TionBot.h"

//=========================
// 🔹 WiFi credentials
//=========================a
const char* ssid = "xxx";
const char* password = "yyy";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String voiceCommand = "";
