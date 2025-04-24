#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char *ssid = "workspace6";  // Enter your Wi-Fi name
const char *password = "passcode6";  // Enter your Wi-Fi password

// MQTT Broker settings
const char *mqtt_broker = "broker.emqx.io";  // Broker address
const char *topic = "emqx/esp32";  // Topic to publish/subscribe to
const char *mqtt_username = "emqx";  // Broker username (for public brokers, it's often 'emqx')
const char *mqtt_password = "public";  // Broker password (for public brokers, it's often 'public')
const int mqtt_port = 1883;  // Port for non-secure MQTT

WiFiClient espClient;
PubSubClient client(espClient);  // Initialize MQTT client

void setup() {
    // Start the Serial monitor
    Serial.begin(115200);
    
    // Connect to Wi-Fi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to Wi-Fi network");
    
    // Set MQTT server details
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);

    // Connect to MQTT broker
    while (!client.connected()) {
        String client_id = "mqttx_38990e29";  // You can create a unique client ID
        client_id += String(WiFi.macAddress());  // Append MAC address for uniqueness
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());

        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Connected to EMQX MQTT broker");
        } else {
            Serial.print("MQTT connection failed with state: ");
            Serial.println(client.state());
            delay(2000);  // Retry after 2 seconds
        }
    }

    // Publish a message to the topic
    client.publish(topic, "Hi, I'm ESP32 ^^");

    // Subscribe to the topic
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    // Print the received message
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
    // Keep the MQTT client loop running to handle incoming messages
    client.loop();
}
