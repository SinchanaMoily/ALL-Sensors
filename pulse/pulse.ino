#define PULSE_PIN A0    // Pulse Sensor connected to GPIO34 (A0)
#define TEMP_PIN A1    // LM35 Sensor connected to GPIO35 (A1)

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // Set ADC to 12-bit (0-4095 range)
}

void loop() {
  // Read and average pulse sensor (improves stability)
  int pulseValue = readAverage(PULSE_PIN, 20);

  // Read LM35 temperature and convert to Celsius
  float voltage = analogRead(TEMP_PIN) * (3.3 / 4095.0); 
  float temperature = voltage * 100; // LM35 outputs 10mV per °C

  // Display readings
  Serial.print("Pulse Value: ");
  Serial.print(pulseValue);
  Serial.print(" | Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // 1-second delay for stability
}

// Function to average multiple ADC readings
int readAverage(int pin, int samples) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delayMicroseconds(500); // Small delay for better accuracy
  }
  return sum / samples;
}
