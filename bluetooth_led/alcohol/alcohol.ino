const int sensorPin = A0;    // MQ-3 connected to analog pin A0
const int ledPin = 13;       // LED connected to digital pin 13
const int threshold = 300;   // Threshold value for alcohol detection

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(2000);  // Allow the sensor to warm up
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Read alcohol sensor value
  Serial.print("Alcohol Sensor Value: ");
  Serial.println(sensorValue);

  // Trigger LED if alcohol level crosses the threshold
  if (sensorValue > threshold) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Alcohol detected!");
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);  // Wait for a second before reading again
}
