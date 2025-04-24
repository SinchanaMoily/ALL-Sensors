#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Initialize the GPS object
TinyGPSPlus gps;

// Define the serial port for GPS communication
HardwareSerial mySerial(1);  // Use Serial1 for GPS

void setup() {
  // Start Serial communication for debugging
  Serial.begin(115200);
  
  // Initialize the GPS serial port
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // RX, TX pins for GPS
  
  Serial.println("GPS6MV2 Experiment with ESP32-S2");
}

void loop() {
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read()); // Feed the data to the GPS object
    
    // Check if a valid GPS fix is obtained
    if (gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
      
      Serial.print("Altitude= ");
      Serial.println(gps.altitude.meters());
      
      Serial.print("Speed= ");
      Serial.println(gps.speed.kmph());
      
      Serial.print("Date= ");
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.println(gps.date.year());
      
      Serial.print("Time= ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.print(gps.time.second());
      Serial.println();
    }
  }
}
