int irSensorPin = 7;
void setup() {
pinMode(irSensorPin, INPUT);
Serial.begin(9600);
}
void loop() {
int irValue = digitalRead(irSensorPin);
if (irValue == LOW) {
Serial.println("Object detected!");           
} else {
Serial.println("No object detected.");
}
delay(500);
}
