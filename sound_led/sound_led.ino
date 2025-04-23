const int soundSensorPin = A0; // Pin for sound sensor
const int threshold = 500;    // Threshold value for detecting sound

void setup() {
  pinMode(42, OUTPUT);    // Set the LED pin as an output
  Serial.begin(9600);         // Start serial communication
}

void loop() {
  int sensorValue = analogRead(soundSensorPin); // Read sound sensor value
  Serial.print("Sound Level: ");
  Serial.println(sensorValue);

  if (sensorValue > threshold) {
    digitalWrite(42, HIGH); // Turn on LED if sound exceeds threshold
  } else {
    digitalWrite(42, LOW);  // Turn off LED if sound is below threshold
  }

  delay(1000); // Delay for 1 second
}
