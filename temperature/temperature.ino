#include <DHT.h>
#define DHTPIN 8  // Pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();  // Initialize the DHT sensor
}
void loop() {
  delay(2000);  // Wait 2 seconds between readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
}
