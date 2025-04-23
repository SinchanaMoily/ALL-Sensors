#include <Ultrasonic.h>
#include <WiFi.h>
#include <HTTPClient.h>

Ultrasonic ultrasonic(12, 13);
const char* ssid = "workspace6";
const char* password = "passcode6";
const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "DL5JDYMBFDK4MBBQ";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  int distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(distance);
    http.begin(url);
    int httpResponseCode = http.GET();
    http.end();
  } else {
    Serial.println("ERROR IN WIFI CONNECTIVITY");
  }

  delay(1000); 
}
