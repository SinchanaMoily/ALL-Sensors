#include <SPI.h>

volatile byte responseData = 0b11111111; // Data to send to Master
volatile byte receivedData = 0;          // Data received from Master

void setup() {
  pinMode(MISO, OUTPUT); // Set MISO as output
  SPCR |= _BV(SPE);      // Enable SPI in Slave mode
  SPCR |= _BV(SPIE);     // Enable SPI interrupt

  Serial.begin(9600);
  Serial.println("Slave is ready.");
}

void loop() {
  delay(100);
}

ISR(SPI_STC_vect) {
  receivedData = SPDR; // Read data sent by Master
  SPDR = responseData; // Load data to send to Master

  Serial.print("Slave received: ");
  Serial.println(receivedData, BIN);
}