const int soundSensorPin = A0;
void setup() {
  Serial.begin(9600); 
}
void loop() {
  int sensorValue = analogRead(soundSensorPin); 
  Serial.print("Sound Level: ");
  Serial.println(sensorValue);
  delay(1000); 
}