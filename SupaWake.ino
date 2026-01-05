#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <config.h>

// twice per week ≈ every 3.5 days
#define SLEEP_SECONDS (3.5 * 24 * 60 * 60)
#define BUTTON_PIN 0

WiFiClientSecure client;

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void querySupabaseDirect() {
  Serial.println("Connecting to Supabase...");

  WiFiClientSecure client;
  client.setInsecure();

  String url = "https://" + String(SUPABASE_HOST) +
               "/rest/v1/" + String(TABLE_NAME) +
               "?select=" + String(COLUMN_NAME) + "&limit=1";

  HTTPClient https;
  if (!https.begin(client, url)) {
    Serial.println("http.begin failed");
    return;
  }

  https.addHeader("apikey", SUPABASE_ANON_KEY);
  https.addHeader("Authorization", "Bearer " + String(SUPABASE_ANON_KEY));
  https.addHeader("Accept", "application/json");

  int httpCode = https.GET();

  if (httpCode > 0) {
    Serial.printf("HTTP %d\n", httpCode);
    String payload = https.getString();
    Serial.println("Supabase response:");
    Serial.println(payload);
  } else {
    Serial.printf("HTTP request failed: %s\n", https.errorToString(httpCode).c_str());
  }

  https.end();
}

void goToSleep() {
  Serial.println("Going to deep sleep...");
  esp_sleep_enable_timer_wakeup((uint64_t)SLEEP_SECONDS * 1000000ULL);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Setup starting: automatic Supabase wakeup.");

  // automatic wakeup (comment out to enable button override in loop)
  connectToWiFi();
  querySupabaseDirect();

  // optional second call after random short delay
  delay(random(5000, 30000));
  querySupabaseDirect();

  delay(1000);
  goToSleep();
}

void loop() {
  // -----------------------------
  // manual button override
  // -----------------------------
  // uncomment this section for manual control or development.
  // lets you trigger a Supabase request by pressing the BOOT button.
  /*
  static bool triggered = false;

  if (digitalRead(BUTTON_PIN) == LOW && !triggered) {
    triggered = true;
    Serial.println("Button pressed!");
    connectToWiFi();
    callSupabase();
    Serial.println("Done. Release button.");
  }

  if (digitalRead(BUTTON_PIN) == HIGH && triggered) {
    triggered = false;
    Serial.println("Ready for next press.");
  }

  delay(50);
  */
}
