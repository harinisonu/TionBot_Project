#include "GetWeather.h"

//=========================
// 🔹 Animation State
//=========================
struct Raindrop {
  int x;
  int y;
  int speed;
};

Raindrop raindrops[NUMDROPS];
bool animationInitialized = false;
bool weatherDataReady = false;

//=========================
// 🔹 WiFi Connection
//=========================
void connectToWiFi() {
  Serial.print(F("Connecting to WiFi: "));
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print(F("WiFi: "));
  display.println(ssid);
  display.display();
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\n✅ WiFi Connected!"));
    Serial.print(F("IP: "));
    Serial.println(WiFi.localIP());
    
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println(F("WiFi Connected!"));
    display.print(F("IP: "));
    display.println(WiFi.localIP());
    display.display();
    delay(2000);
  } else {
    Serial.println(F("\n❌ WiFi failed!"));
    display.clearDisplay();
    display.setCursor(0, 28);
    display.println(F("WiFi Failed!"));
    display.display();
    delay(3000);
  }
}

//=========================
// 🔹 Fetch Weather Data
//=========================
void fetchWeatherData() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("❌ WiFi disconnected!"));
    weatherDataReady = false;
    return;
  }
  
  WiFiClient client;
  HTTPClient http;
  
  String apiUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + 
                  String(city) + "&appid=" + String(apiKey) + "&units=metric";
  
  Serial.println(F("🌐 Requesting weather..."));
  http.begin(client, apiUrl);
  http.setTimeout(5000);
  
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);
    
    if (!error) {
      temperature = doc["main"]["temp"].as<float>();
      humidity = doc["main"]["humidity"].as<int>();
      weather = doc["weather"][0]["main"].as<String>();
      description = doc["weather"][0]["description"].as<String>();
      
      weatherDataReady = true;
      animationInitialized = false;
      
      Serial.println(F("✅ Weather received:"));
      Serial.print(F("  Temp: ")); Serial.print(temperature); Serial.println(F("°C"));
      Serial.print(F("  Humidity: ")); Serial.print(humidity); Serial.println(F("%"));
      Serial.print(F("  Weather: ")); Serial.println(weather);
    } else {
      Serial.print(F("JSON error: "));
      Serial.println(error.c_str());
      weatherDataReady = false;
    }
  } else {
    Serial.print(F("HTTP Error: "));
    Serial.println(http.errorToString(httpCode));
    weatherDataReady = false;
  }
  
  http.end();
}

//=========================
// 🔹 Initialize Animation
//=========================
void initializeWeatherAnimation() {
  for (int i = 0; i < NUMDROPS; i++) {
    raindrops[i].x = random(0, SCREEN_WIDTH - LOGO_WIDTH);
    raindrops[i].y = random(-LOGO_HEIGHT, SCREEN_HEIGHT / 2);
    raindrops[i].speed = random(1, 4);
  }
  animationInitialized = true;
}

//=========================
// 🔹 Update Weather Animation (Non-Blocking)
//=========================
void updateWeatherAnimation() {
  if (!weatherDataReady) return;
  
  if (!animationInitialized) {
    initializeWeatherAnimation();
  }
  
  display.clearDisplay();
  
  // Select weather icon based on condition
  const uint8_t* weatherIcon = icon_unknown_16;
  weatherIcon = dropLet;
  // if (weather == "Clear") weatherIcon = icon_sun_16;
  // else if (weather == "Rain") weatherIcon = dropLet;
  // else if (weather == "Drizzle") weatherIcon = icon_drizzle_16;
  // else if (weather == "Mist" || weather == "Haze" || weather == "Fog") weatherIcon = icon_mist_16;
  // else if (weather == "Clouds") weatherIcon = icon_clouds_16;
  // else if (weather == "Thunderstorm") weatherIcon = icon_thunder_16;
  
  // Draw animated weather icons (top half)
  for (int i = 0; i < NUMDROPS; i++) {
    display.drawBitmap(raindrops[i].x, raindrops[i].y, weatherIcon, 
                       LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
    
    // Update positions
    raindrops[i].y += raindrops[i].speed;
    if (raindrops[i].y >= SCREEN_HEIGHT / 2) {
      raindrops[i].x = random(0, SCREEN_WIDTH - LOGO_WIDTH);
      raindrops[i].y = -LOGO_HEIGHT;
      raindrops[i].speed = random(1, 4);
    }
  }
  
  // Draw weather info (bottom half)
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, SCREEN_HEIGHT / 2 + 2);
  display.print(city);
  display.println(F(" Weather"));
  
  display.setCursor(0, SCREEN_HEIGHT / 2 + 14);
  display.print(F("Temp: "));
  display.print(temperature, 1);
  display.println(F(" C"));
  
  // display.setCursor(0, SCREEN_HEIGHT / 2 + 24);
  // display.print(F("Humidity: "));
  // display.print(humidity);
  // display.println(F("%"));
  
  display.setCursor(0, SCREEN_HEIGHT / 2 + 24);
  display.print(F("Cond: "));
  display.print(F("Rain"));
  // display.println(weather);
  
  display.display();
}
