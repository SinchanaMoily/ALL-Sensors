#define BLYNK_PRINT Serial
#define IR_SENSOR1 2
#define IR_SENSOR2 4
#define IR_SENSOR3 5

#define BLYNK_TEMPLATE_ID "TMPL3c3neUMKc"
#define BLYNK_TEMPLATE_NAME "IOT PARKING"
#define BLYNK_AUTH_TOKEN "OODvak3HJQFAhTDNIiApuuGHjdUj4rVn"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Abhishek";
char pass[] = "12345678";
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(IR_SENSOR1, INPUT);
  pinMode(IR_SENSOR2, INPUT);
  pinMode(IR_SENSOR3, INPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, checkParkingStatus); // Check every 500ms
}

void checkParkingStatus() {
  // IR sensors return LOW when object detected
  int slot1 = !digitalRead(IR_SENSOR1); // Invert the reading
  int slot2 = !digitalRead(IR_SENSOR2);
  int slot3 = !digitalRead(IR_SENSOR3);
  
  // Update Blynk LEDs - ON when car detected (255), OFF when empty (0)
  Blynk.virtualWrite(V0, slot1 ? 255 : 0);
  Blynk.virtualWrite(V1, slot2 ? 255 : 0);
  Blynk.virtualWrite(V2, slot3 ? 255 : 0);
  
  // Print status
  Serial.print("Slot 1: ");
  Serial.println(slot1 ? "Car Present" : "Empty");
  Serial.print("Slot 2: ");
  Serial.println(slot2 ? "Car Present" : "Empty");
  Serial.print("Slot 3: ");
  Serial.println(slot3 ? "Car Present" : "Empty");
}

void loop() {
  Blynk.run();
  timer.run();
}