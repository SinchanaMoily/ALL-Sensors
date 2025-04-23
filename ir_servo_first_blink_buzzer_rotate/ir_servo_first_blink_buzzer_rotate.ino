#include <ESP32Servo.h>
Servo entryServo;
int irSensorPin =7 ;    // IR sensor pin
int entryServoPin =6 ;// Servo motor pin
int buzzerPin= 5  ;  
int LedPin =42 ; 

void setup() {
  entryServo.attach(entryServoPin);
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LedPin, OUTPUT);

  entryServo.write(0); //  closed initially
  Serial.begin(9600);
}

void loop() {
  int irState = digitalRead(irSensorPin);

  if (irState == LOW) { // Object detected
    Serial.println("Object detected");
    entryServo.write(90);          // Open the gate
    delay(1000); 
    // Blink LED and buzz for 3 seconds
    for (int i = 0; i < 6; i++) {  
      digitalWrite(LedPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(250);  // ON duration
      digitalWrite(LedPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(250);  // OFF duration
    }

                      // Keep gate open for 1 second
  } else {
    Serial.println("No object detected.");
    
    entryServo.write(0);           // Forcefully close the gate
  }
  delay(500); // Small delay for stability
}
