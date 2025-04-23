#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// WiFi Credentials
const char* ssid = "workspace6";
const char* password = "passcode6";

// Telegram Credentials
#define BOT_TOKEN "7664092302:AAEb1zxSgVqhF4DuKh_AlPnbnvX-GKhmDBE"
#define CHAT_ID "1853029209"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

const int ledPin = 42;  // LED connected to GPIO 2

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  bot.sendMessage(CHAT_ID, "ESP32 started! Ready to send LED notifications.", "");
}

void loop() {
  // Simulate LED turning on
  digitalWrite(ledPin, HIGH);
  Serial.println("LED is ON");
  
  // Send Telegram Notification
  bot.sendMessage(CHAT_ID, "LED is ON!", "");

  delay(5000); // Wait 5 seconds before turning off the LED

  digitalWrite(ledPin, LOW);
  Serial.println("LED is OFF");
  bot.sendMessage(CHAT_ID, "LED is OFF!", "");
  delay(5000); // Wait before next cycle
}
