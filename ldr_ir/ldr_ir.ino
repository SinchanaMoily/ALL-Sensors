#define LDR_PIN A0
#define IR_SENSOR_PIN 7

int lightThreshold = 500; // Threshold for LDR

void setup() {
  Serial.begin(9600);         // Initialize Serial Monitor
  pinMode(LDR_PIN, INPUT);    // Set LDR pin as input
  pinMode(IR_SENSOR_PIN, INPUT); // Set IR sensor pin as input
}

void loop() {
  // LDR Sensor Logic
  int ldrValue = analogRead(LDR_PIN); // Read LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue > lightThreshold) {
    Serial.println("It's dark.");
  } else {
    Serial.println("It's bright.");
  }

  // IR Sensor Logic
  int irValue = digitalRead(IR_SENSOR_PIN); // Read    IR sensor value
  if (irValue == LOW) {
    Serial.println("Object detected!");
  } else {
    Serial.println("No object detected.");
  }

  delay(500); // Delay before repeating the loop
}
