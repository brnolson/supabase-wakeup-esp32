# ESP32 SupaWake

![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)
![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-orange.svg)
![Tested on Eleego32](https://img.shields.io/badge/Tested%20on-Eleego32-blueviolet)

Keep your Supabase database awake using a low-power ESP32. Performs a simple GET query twice a week to prevent your database from spinning down due to inactivity.

## Features
- Automatic `GET` requests to Supabase twice per week
- Optional manual button trigger for development/testing
- Low-power deep sleep between wakeups
- Configurable via `config.h`

## Setup
**1. Install ESP32 board support in Arduino IDE:**
  - File → Preferences → Add URL: https://dl.espressif.com/dl/package_esp32_index.json
  - Tools → Board → Board Manager → install esp32 by Espressif Systems
**2. Clone the repository**
```bash
git clone https://github.com/brnolson/supabase-wakeup-esp32.git
```
**3. Configure `config.h`**
  - Copy `config.example.h` → `config.h`
  - Fill in WiFi and Supabase credentials
```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* SUPABASE_HOST = "YOUR_PROJECT_ID.supabase.co";
const char* SUPABASE_ANON_KEY = "YOUR_ANON_KEY";
const char* TABLE_NAME = "save_the_dates";
const char* COLUMN_NAME = "id";
```
**4. Upload sketch to ESP32**
- Open `SupaWake.ino` in Arduino IDE
- Select your ESP32 device and the correct port
- Click Upload and monitor output at 115200 baud

## How it works
- ESP32 wakes up, connects to WiFi
- Sends two `GET` requests to Supabase (second delayed randomly)
- Goes into deep sleep for ~3.5 days
- Repeats automatically

## License

MIT License – free to use, modify, and share

<hr>
© 2026 Brenen Olson