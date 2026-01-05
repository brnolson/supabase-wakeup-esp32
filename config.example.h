#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Supabase info
const char* SUPABASE_HOST = "YOUR_PROJECT_ID.supabase.co"; // ensure no https://
const char* SUPABASE_ANON_KEY = "YOUR_ANON_KEY";

// Table info
const char* TABLE_NAME = "save_the_dates";
const char* COLUMN_NAME = "id";

#endif
