#include <SPI.h>

byte sentData = 0b10101010;         // Data to send to Slave
byte receivedData = 0;              // Data received from Slave

void setup() {
 

  // Initialize SPI
  SPI.begin();
  pinMode(SS, OUTPUT); // SS must be set as OUTPUT for Master
  digitalWrite(SS, HIGH); // Set SS HIGH initially (idle state)

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Master is ready.");
}

void loop() {
  // Simulate sending and receiving data periodically
  digitalWrite(SS, LOW); // Enable Slave
  receivedData = SPI.transfer(sentData); // Exchange data with Slave
  digitalWrite(SS, HIGH); // Disable Slave

  // Print received data to Serial Monitor
  Serial.print("Master received: ");
  Serial.println(receivedData, BIN);




  // Add delay for visualization
  delay(1000);


}