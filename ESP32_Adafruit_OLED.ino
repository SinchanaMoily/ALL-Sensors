#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h> // Include the ESP32Servo library

// Wi-Fi and ThingSpeak configuration
const char* WIFI_SSID = "workspace6";
const char* WIFI_PASSWORD = "passcode6";
const char* THINGSPEAK_SERVER = "http://api.thingspeak.com/update";
const char* THINGSPEAK_API_KEY = "MIOKKG16EUL3HZ0Z";

// Rain sensor and servo configuration
const int RAIN_SENSOR = A0; // Analog pin for rain sensor
Servo wiperServo;          // Servo object
const int SERVO_PIN = 8;    // GPIO pin for servo
const int RAIN_THRESHOLD = 5000; // Threshold for detecting rain

void setup() {
  Serial.begin(9600);
  pinMode(RAIN_SENSOR, INPUT);
  wiperServo.attach(SERVO_PIN); // Attach the servo to a valid GPIO pin
  connectToWiFi();
}

void loop() {
  int rainIntensity = analogRead(RAIN_SENSOR);
  Serial.print("Rain Sensor Reading: ");
  Serial.println(rainIntensity);

  handleWiperMovement(rainIntensity);
  sendToThingSpeak(rainIntensity);

  delay(2000); // Adjust delay for data sending frequency
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected successfully.");
}

void handleWiperMovement(int rainIntensity) {
  if (rainIntensity < RAIN_THRESHOLD) {
    Serial.println("Rain detected! Activating wiper...");
    rotateWiper(); // Rotate wiper continuously while rain is detected
  } else {
    Serial.println("No rain detected.");
    wiperServo.write(0); // Reset the servo to its initial position
  }
}

void rotateWiper() {
  static unsigned long lastWiperMove = 0;
  const int wiperInterval = 1000; // Interval for wiper movement (ms)

  if (millis() - lastWiperMove >= wiperInterval) {
    static bool toggleWiper = false;

    if (toggleWiper) {
      wiperServo.write(90); // Rotate servo to 90 degrees
    } else {
      wiperServo.write(0); // Rotate servo back to 0 degrees
    }

    toggleWiper = !toggleWiper;
    lastWiperMove = millis();
  }
}

void sendToThingSpeak(int rainIntensity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String requestURL = String(THINGSPEAK_SERVER) + "?api_key=" + THINGSPEAK_API_KEY + "&field1=" + String(rainIntensity);

    http.begin(requestURL);
    int responseCode = http.GET();

    if (responseCode > 0) {
      Serial.println("Data sent to ThingSpeak successfully. Response code: " + String(responseCode));
    } else {
      Serial.println("Failed to send data to ThingSpeak. HTTP response code: " + String(responseCode));
    }

    http.end();
  } else {
    Serial.println("Wi-Fi disconnected. Unable to send data.");
  }
}