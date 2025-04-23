#include <ESP32Servo.h> // Include the ESP32Servo library

Servo entryServo;

int irSensorPin = 12;   // IR sensor pin
int entryServoPin = 7; // Servo motor pin

void setup() {
  entryServo.attach(entryServoPin); 
  pinMode(irSensorPin, INPUT);      

  entryServo.write(0); 

  Serial.begin(9600);
}

void loop() {
  int irState = digitalRead(irSensorPin);

  if (irState == LOW) { // Object detected
    Serial.println("Object detected at entry! Opening entry gate...");
    entryServo.write(90); // Rotate servo to 90 degrees
    delay(1000);          // Keep it open for 1 second
  } else {
    Serial.println("No object detected. Entry gate remains closed.");
    entryServo.write(0);
  }

  delay(500); 
}
