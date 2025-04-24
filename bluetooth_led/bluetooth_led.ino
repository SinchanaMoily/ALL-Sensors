#include <SoftwareSerial.h>

// Define RX and TX pins for SoftwareSerial
SoftwareSerial BT(10, 11); // TX, RX

#define LED_PIN 13 // LED connected to Pin 13

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  digitalWrite(LED_PIN, LOW); // Ensure LED is off initially
  
  Serial.begin(9600); // Serial monitor for debugging
  BT.begin(9600); // Start Bluetooth communication at 9600 baud
  Serial.println("Bluetooth LED Control Initialized");
}

void loop() {
  if (BT.available()) { // Check if data is available from Bluetooth
    char command = BT.read(); // Read the command
    Serial.println(command); // Print command to Serial Monitor for debugging
    
    if (command == '1') { // Turn ON LED
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    } 
    else if (command == '0') { // Turn OFF LED
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
}
