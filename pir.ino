#define pirSensorPin 2  // PIR sensor connected to digital pin 2

void setup() {
  pinMode(pirSensorPin, INPUT); // Set PIR sensor as input
  Serial.begin(9600);           // Start serial communication
}

void loop() {
  int motionDetected = digitalRead(pirSensorPin); // Read PIR sensor state

  if (motionDetected == HIGH) { // Motion detected
    Serial.println("Motion detected!");
    delay(2000);                // Wait for 2 seconds to avoid multiple detections
  } else {
    Serial.println("No motion.");
    delay(500);                 // Small delay for stability
  }
}
