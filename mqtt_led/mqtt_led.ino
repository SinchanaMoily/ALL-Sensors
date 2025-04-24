#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> // Include the Arduino JSON library

// WiFi credentials
const char *ssid = "workspace6";
const char *password = "passcode6";

// MQTT Broker details
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "led/control";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

// LED Pin
const int ledPin = 5; // GPIO5

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Set up LED pin
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Ensure LED is OFF initially

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Connect to MQTT broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);

    while (!client.connected()) {
        String client_id = "mqttx_" + String(WiFi.macAddress());
        Serial.printf("Connecting to MQTT broker with client ID: %s\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect. State: ");
            Serial.println(client.state());
            delay(2000);
        }
    }

    // Subscribe to the topic
    client.subscribe(topic);
    Serial.println("Subscribed to topic: " + String(topic));
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");

    String jsonPayload;

    // Concatenate the payload into a string
    for (int i = 0; i < length; i++) {
        jsonPayload += (char)payload[i];
    }
    Serial.println(jsonPayload);

    // Parse the JSON message
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonPayload);

    if (error) {
        Serial.print("JSON deserialization failed: ");
        Serial.println(error.c_str());
        return;
    }

    // Extract the value of "msg"
    const char *msg = doc["msg"];
    if (strcmp(msg, "ON") == 0) {
        digitalWrite(ledPin, HIGH);
        Serial.println("LED turned ON");
    } else if (strcmp(msg, "OFF") == 0) {
        digitalWrite(ledPin, LOW);
        Serial.println("LED turned OFF");
    } else {
        Serial.println("Unknown command");
    }
}

void loop() {
    client.loop();
}

