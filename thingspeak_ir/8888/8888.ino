#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "ITL8B6CKIMPV5KLO";

#define IR_PIN 8
void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(2000);
  int irValue = digitalRead(IR_PIN);
 if (irValue == LOW) {
    Serial.println("Obstacle detected!");
  delay(100);                    
  } else {
    Serial.println("Obstacle not detected!");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(irValue);

    http.begin(url);
    int httpResponseCode = http.GET();

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}