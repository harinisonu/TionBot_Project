#include "TionBot.h"
#include "Emotes.h"
#include "GetWeather.h"
#include "GetTime.h" 
#include <BlynkSimpleEsp8266.h>

//=========================
// 🔹 External Variables
//=========================
extern bool weatherDataReady;  
extern bool rtcInitialized;

//=========================
// 🔹 State Management
//=========================
enum DisplayMode {
  EMOTE_MODE,
  WEATHER_MODE,
  TIME_MODE
};

DisplayMode currentMode = EMOTE_MODE;
unsigned long modeStartTime = 0;
const unsigned long WEATHER_DISPLAY_DURATION = 10000; // 10 seconds
unsigned long lastTimeUpdate = 0;
const unsigned long TIME_UPDATE_INTERVAL = 500;
const unsigned long TIME_DISPLAY_DURATION = 10000;


//=========================
// 🔹 Timing Variables (Non-Blocking)
//=========================
unsigned long lastEmoteUpdate = 0;
unsigned long lastWeatherAnimation = 0;
unsigned long lastWeatherFetch = 0;
const unsigned long EMOTE_FRAME_INTERVAL = 80;        // 80ms per frame
const unsigned long WEATHER_ANIM_INTERVAL = 100;      // 100ms for weather drops
const unsigned long WEATHER_FETCH_MIN_INTERVAL = 300000; // 5 minutes

//=========================
// 🔹 Setup
//=========================
void setup() {
  Serial.begin(115200);
  delay(100);
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 28);
  display.println(F("TionBot v1.0"));
  display.display();
  delay(2000);
  
  // Connect to WiFi
  connectToWiFi();
  initializeRTC();
  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println(F("✅ TionBot ready!"));
  Serial.println(F("Commands: 'w'=weather, 'e'=emote, 't'=time"));
  
  display.clearDisplay();
  display.display();
}

//=========================
// 🔹 Main Loop (Non-Blocking)
//=========================
void loop() {
  Blynk.run(); // Must run continuously without blocking
  
  unsigned long currentMillis = millis();
  
  // State machine for display modes
  switch (currentMode) {
    case EMOTE_MODE:
      // Update emote animation at controlled intervals
      if (currentMillis - lastEmoteUpdate >= EMOTE_FRAME_INTERVAL) {
        updateEmoteAnimation();
        lastEmoteUpdate = currentMillis;
      }
      break;
      
    case WEATHER_MODE:
      // Update weather animation
      if (currentMillis - lastWeatherAnimation >= WEATHER_ANIM_INTERVAL) {
        updateWeatherAnimation();
        lastWeatherAnimation = currentMillis;
      }
      
      // Auto-return to emote mode after duration
      if (currentMillis - modeStartTime >= WEATHER_DISPLAY_DURATION) {
        currentMode = EMOTE_MODE;
        resetEmoteAnimation();
        display.clearDisplay();
        Serial.println(F("🔄 Back to emote mode"));
      }
      break;
    case TIME_MODE:  // ← ADD THIS ENTIRE CASE
      if (currentMillis - lastTimeUpdate >= TIME_UPDATE_INTERVAL) {
        updateTimeDisplay();
        lastTimeUpdate = currentMillis;
      }
      
      if (currentMillis - modeStartTime >= TIME_DISPLAY_DURATION) {
        currentMode = EMOTE_MODE;
        resetEmoteAnimation();
        display.clearDisplay();
        Serial.println(F("🔄 Back to emote mode"));
      }
      break;
  }
  
  // Handle serial commands (non-blocking)
  if (Serial.available()) {
    voiceCommand = Serial.readStringUntil('\n');
    voiceCommand.trim();
    voiceCommand.toLowerCase();
    
    if (voiceCommand == "w" || voiceCommand == "weather") {
      handleWeatherRequest();
    } else if (voiceCommand == "e" || voiceCommand == "emote") {
      currentMode = EMOTE_MODE;
      resetEmoteAnimation();
      Serial.println(F("😊 Emote mode activated"));
    } else if (voiceCommand == "help") {
      Serial.println(F("Commands: w/weather, e/emote"));
    }else if (voiceCommand == "t" || voiceCommand == "time") { 
    handleTimeRequest();
  }
  }
}

//=========================
// 🔹 Blynk Virtual Pin Handler
//=========================
BLYNK_WRITE(V1) {
  String command = param.asStr();
  command.trim();
  command.toLowerCase();
  
  if (command == "w" || command == "weather") {
    handleWeatherRequest();
  } else if (command == "e" || command == "emote") {
    currentMode = EMOTE_MODE;
    resetEmoteAnimation();
  }else if (command == "t" || command == "time") {
    handleTimeRequest();
  }
}

//=========================
// 🔹 Weather Request Handler
//=========================
void handleWeatherRequest() {
  unsigned long currentMillis = millis();
  
  // Throttle API requests (protect against quota limits)
  /*
  if (currentMillis - lastWeatherFetch < WEATHER_FETCH_MIN_INTERVAL) {
    unsigned long remaining = (WEATHER_FETCH_MIN_INTERVAL - (currentMillis - lastWeatherFetch)) / 1000;
    Serial.print(F("⏳ Wait "));
    Serial.print(remaining);
    Serial.println(F(" sec before next fetch"));
    
    // Show cached weather if available
    if (weatherDataReady) {
      currentMode = WEATHER_MODE;
      modeStartTime = currentMillis;
      Serial.println(F("📊 Showing cached weather"));
    }
    return;
  }*/
  
  Serial.println(F("🌐 Fetching weather..."));
  fetchWeatherData();
  
  if (weatherDataReady) {
    currentMode = WEATHER_MODE;
    modeStartTime = currentMillis;
    lastWeatherFetch = currentMillis;
    Serial.println(F("✅ Weather displayed"));
  } else {
    Serial.println(F("Weather fetch failed"));
  }
}

void handleTimeRequest() {
  if (!rtcInitialized) {
    Serial.println(F("❌ RTC not initialized!"));
    return;
  }
  
  currentMode = TIME_MODE;
  modeStartTime = millis();
  Serial.println(F("⏰ Time display activated"));
}

