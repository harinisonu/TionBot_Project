# TionBot_Project

# **TionBot - UART/BLYNK Text-Activated OLED Weather & Time Display**

> An ESP8266-based IoT desk companion that displays real-time weather, accurate time, and animated emotional expressions.

---

## **📖 Overview**

TionBot is a smart desk assistant that combines weather monitoring, precision timekeeping, and personality through animated OLED displays. Built on the ESP8266 NodeMCU platform, it integrates cloud APIs, real-time clock hardware, and IoT connectivity for a responsive and engaging user experience.

### **✨ Key Features**

- 🌤️ **Real-time Weather Display** - Fetches data from OpenWeatherMap API with animated weather icons
- ⏰ **Precision Clock** - DS3231 RTC module with ±2ppm accuracy and battery backup
- 😊 **Animated Expressions** - 50-frame emotional eye animations
- ☁️ **Cloud Control** - Remote commands via Blynk IoT platform
- 🎤 **Voice Ready** - Architecture supports Google Assistant integration (IFTTT)
- 📱 **Multiple Interfaces** - Serial commands, Blynk app, and future voice control
- ⚡ **Non-Blocking Design** - Responsive architecture maintains stable WiFi/Blynk connections

---

## **🛠️ Hardware Requirements**

| Component | Specifications | Quantity | Purpose |
|-----------|---------------|----------|---------|
| **ESP8266 NodeMCU** | 80MHz, 64KB RAM, WiFi | 1 | Main processor |
| **0.96" OLED Display** | 128×64, I2C (SSD1306) | 1 | Visual output |
| **DS3231 RTC Module** | ±2ppm accuracy, I2C | 1 | Timekeeping |
| **CR2032 Battery** | 3V coin cell | 1 | RTC backup |
| **Breadboard** | 830 points | 1 | Prototyping |
| **Jumper Wires** | M-M, M-F | 10+ | Connections |
| **USB Cable** | Micro-USB | 1 | Programming/Power |

**Total Cost:** ~₹820 ($10 USD)

***

## **💻 Software Requirements**

### **Development Tools**
- Arduino IDE 1.8.x or 2.x
- USB-to-Serial driver (CP2102/CH340)

### **Arduino Libraries**
```
Adafruit SSD1306      v2.5.7+    (OLED display)
Adafruit GFX          v1.11.0+   (Graphics)
RTClib                v2.1.1+    (DS3231 RTC)
ArduinoJson           v6.21.0+   (JSON parsing)
Blynk                 v1.3.2+    (IoT platform)
ESP8266WiFi           (Built-in) (WiFi stack)
ESP8266HTTPClient     (Built-in) (HTTP requests)
```

### **Cloud Services**
- [OpenWeatherMap API](https://openweathermap.org/api) (Free tier: 1000 calls/day)
- [Blynk IoT Platform](https://blynk.cloud) (Free tier available)

***

## **🔌 Hardware Setup**

### **Wiring Diagram**

```
OLED Display (SSD1306)          DS3231 RTC Module
┌─────────────┐                 ┌─────────────┐
│ VCC → 3.3V  │                 │ VCC → 3.3V  │
│ GND → GND   │                 │ GND → GND   │
│ SCL → D1    │ ←────I2C────→  │ SCL → D1    │
│ SDA → D2    │                 │ SDA → D2    │
└─────────────┘                 └─────────────┘
        │                               │
        └───────────────┬───────────────┘
                        │
                  ESP8266 NodeMCU
                ┌─────────────────┐
                │   D1 (GPIO5)    │ ← I2C SCL (shared)
                │   D2 (GPIO4)    │ ← I2C SDA (shared)
                │   3.3V          │ ← Power supply
                │   GND           │ ← Ground
                │   USB           │ ← Programming/Power
                └─────────────────┘
```

### **I2C Address Map**
- **0x3C** - SSD1306 OLED Display
- **0x68** - DS3231 RTC
- **0x57** - AT24C32 EEPROM (on RTC module)

***


## **🎮 Usage**

### **Serial Commands**

Open Serial Monitor (115200 baud) and send:

| Command | Action | Display Duration |
|---------|--------|------------------|
| `e` or `emote` | Show animated expressions | Continuous |
| `w` or `weather` | Display current weather | 10 seconds |
| `t` or `time` | Show RTC clock | 10 seconds |
| `reset` | Reset weather fetch timer | Immediate |
| `help` | Show available commands | Immediate |

### **Blynk App Control**

1. Open Blynk app
2. Send text commands to Virtual Pin V1:
   - `w` → Fetch and display weather
   - `e` → Show emote animations
   - `t` → Display time

### **Display Modes**

#### **EMOTE MODE** (Default)
- 50-frame animated eye expressions
- Frame rate: 80ms/frame (12.5 FPS)
- Total animation cycle: 4 seconds
- Loops continuously

#### **WEATHER MODE** (Command: `w`)
- Temperature, humidity, weather condition
- Animated weather icons (sun, rain, clouds, etc.)
- 10 falling icons animation (100ms refresh)
- Auto-returns to emote mode after 10 seconds
- **Rate limit:** 1 API call per 5 minutes

#### **TIME MODE** (Command: `t`)
- Date: Day, DD/MM/YYYY
- Time: HH:MM with blinking colon
- Seconds: Large display below
- Updates every 500ms
- Auto-returns to emote mode after 10 seconds

***

## **⚙️ Configuration Options**

### **Timing Adjustments** (`TionBot.ino`)

```cpp
// Animation speeds
const unsigned long EMOTE_FRAME_INTERVAL = 80;        // Emote speed (ms)
const unsigned long WEATHER_ANIM_INTERVAL = 100;      // Weather animation (ms)
const unsigned long TIME_UPDATE_INTERVAL = 500;       // Clock refresh (ms)

// Display durations
const unsigned long WEATHER_DISPLAY_DURATION = 10000; // Weather timeout (ms)
const unsigned long TIME_DISPLAY_DURATION = 10000;    // Time timeout (ms)

// API rate limiting
const unsigned long WEATHER_FETCH_MIN_INTERVAL = 300000; // 5 minutes
```

### **Weather Icons Customization** (`GetWeather.cpp`)

Modify icon mappings in `updateWeatherAnimation()`:
```cpp
if (weather == "Clear") weatherIcon = icon_sun_16;
else if (weather == "Rain") weatherIcon = dropLet;
// Add custom weather conditions here
```

### **RTC Time Setting** (`Time.ino`)

**Auto-set to compile time:**
```cpp
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
```

**Manual set:**
```cpp
rtc.adjust(DateTime(2025, 11, 10, 22, 30, 0)); // YYYY, MM, DD, HH, MM, SS
```

***

## **🔧 Troubleshooting**

### **Issue: OLED Not Displaying**
**Solution:**
- Verify I2C connections (SDA→D2, SCL→D1)
- Check I2C address with scanner sketch (should be 0x3C)
- Try alternate address in code: `0x3D`

### **Issue: RTC Not Found**
**Solution:**
- Check I2C connections (SDA→D2, SCL→D1)
- Verify CR2032 battery is installed
- Run I2C scanner (should detect 0x68)
- Ensure both OLED and RTC use 3.3V power

### **Issue: WiFi Connection Failed**
**Solution:**
- Verify SSID and password are correct
- Check 2.4GHz WiFi (ESP8266 doesn't support 5GHz)
- Move closer to router
- Check Serial Monitor for error messages

### **Issue: Weather Not Updating**
**Solution:**
- Verify API key is valid
- Check city name spelling
- Rate limit: Wait 5 minutes between requests
- Use `reset` command to bypass cooldown
- Check Serial Monitor for HTTP error codes

### **Issue: Blynk Not Connecting**
**Solution:**
- Verify Template ID and Auth Token
- Ensure Virtual Pin V1 is configured as String type
- Check internet connectivity
- Try re-uploading with correct credentials

***

## **🚀 Future Enhancements**

### **Planned Features**
- [ ] Google Assistant voice control via IFTTT webhooks
- [ ] DHT22 sensor for local temperature/humidity
- [ ] 5-day weather forecast display
- [ ] News headlines (RSS feed integration)

### **Hardware Upgrades**
- [ ] ESP32 migration (Bluetooth, more RAM)
- [ ] Color OLED display (128×128 RGB)
- [ ] Battery operation with solar charging
- [ ] 3D printed custom enclosure
- [ ] Touch sensor for interaction
- [ ] Light sensor for auto-brightness

***

## **📊 Technical Specifications**

### **Performance Metrics**
- **Boot Time:** ~5 seconds (including WiFi connect)
- **Command Response:** <50ms
- **Weather Fetch Time:** 1-3 seconds
- **Animation Frame Rate:** 12.5 FPS (80ms/frame)
- **Clock Update Rate:** 2 Hz (500ms)
- **Memory Usage:** 45KB/64KB RAM (70%)
- **Flash Usage:** 380KB/4MB (9.5%)
- **Power Consumption:** ~100mA @ 5V typical

### **API Limits**
- **OpenWeatherMap Free Tier:** 1000 calls/day (1 per 86 seconds)
- **TionBot Rate Limit:** 1 call per 5 minutes (288 calls/day)
- **Blynk Free Tier:** Unlimited datastream updates

***

### **Code Style**
- Use Arduino-style function naming (camelCase)
- Comment complex logic sections
- Keep functions under 50 lines
- Use PROGMEM for large constant arrays

***

## **👤 Author**

**HARINI B R**
- GitHub: [@harinisonu](https://github.com/harinisonu)
- Project Link: [https://github.com/harinisonu/TionBot_Project](https://github.com/harinisonu/TionBot_Project)

***

## **🙏 Acknowledgments**

- **Adafruit Industries** - SSD1306 and GFX libraries
- **ESP8266 Community** - Arduino core for ESP8266
- **Blynk Team** - IoT platform and libraries
- **OpenWeatherMap** - Weather API service
- **RTClib Contributors** - DS3231 RTC library
- **Arduino Community** - Documentation and support

***

## **📚 Resources**

### **Documentation**
- [ESP8266 Arduino Core Docs](https://arduino-esp8266.readthedocs.io/)
- [SSD1306 OLED Datasheet](https://www.adafruit.com/product/326)
- [DS3231 RTC Datasheet](https://www.maximintegrated.com/en/products/DS3231.html)
- [OpenWeatherMap API Docs](https://openweathermap.org/api)
- [Blynk Documentation](https://docs.blynk.io/)

### **Tutorials**
- [Getting Started with ESP8266](https://randomnerdtutorials.com/getting-started-with-esp8266/)
- [OLED Display Tutorial](https://randomnerdtutorials.com/esp8266-0-96-inch-oled-display-with-arduino-ide/)
- [DS3231 RTC Guide](https://randomnerdtutorials.com/esp8266-nodemcu-ds3231-real-time-clock-rtc/)

## **⭐ Show Your Support**

Give a ⭐ if this project helped you! Share your build on social media with #TionBot

---

**Made with ❤️ and ESP8266**

*Last Updated: November 10, 2025*

[1](https://randomnerdtutorials.com/projects-esp8266/)
[2](https://www.instructables.com/ESP8266-Home-Automation-Project-Using-NodeMCU-and-/)
[3](https://binnes.github.io/esp8266Workshop/pdf/esp8266Workshop.pdf)
[4](https://github.com/SazidulAlam47/iot-fan-light-control)
[5](https://www.youtube.com/watch?v=fhEU80xJi-g)
[6](https://www.youtube.com/watch?v=ZPUg4Uw3A0E)
[7](https://www.scribd.com/document/737039282/IoT-PROJECT)
[8](https://www.instructables.com/ESP8266-Projects/)
[9](https://randomnerdtutorials.com/getting-started-with-esp8266-wifi-transceiver-review/)
