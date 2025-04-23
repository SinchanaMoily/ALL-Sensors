#include <Ultrasonic.h>
#include <ESP32Servo.h>

const int irPin = 2; // IR sensor input
const int trigPin1 = 3; // Trigger pin for the first ultrasonic sensor
const int echoPin1 = 4; // Echo pin for the first ultrasonic sensor
const int trigPin2 = 5; // Trigger pin for the second ultrasonic sensor
const int echoPin2 = 6; // Echo pin for the second ultrasonic sensor
const int redLedPin = 7; // Red LED pin
const int greenLedPin = 8; // Green LED pin
const int servoPin = 9; // Servo motor pin

Ultrasonic ultrasonic1(trigPin1, echoPin1);
Ultrasonic ultrasonic2(trigPin2, echoPin2);

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(irPin, INPUT);
}

void loop() {
  if (digitalRead(irPin) == HIGH) {
    myServo.write(90); // Rotate to 90 degrees
  } else {
    myServo.write(0);
  }

  long distance1 = ultrasonic1.read();
  long distance2 = ultrasonic2.read();

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (distance1 < 20 && distance2 < 20) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  } else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
  delay(200);
}
