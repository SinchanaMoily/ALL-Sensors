#include <AccelStepper.h>

// Initialize the stepper motor with the 4 pins
AccelStepper stepper(4, 11, 12, 13, 14);

const int buttonPin = 15; // Button connected to GPIO 33
bool lastButtonState = LOW;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP); // Set button as input
  stepper.setMaxSpeed(1000); // Set motor speed
  stepper.setSpeed(200);
}

void loop() {
  // Read button press
  bool buttonState = digitalRead(buttonPin) == LOW;

  if (buttonState && !lastButtonState) {
    // Button Pressed
    Serial.println("Button Pressed - Rotating Stepper!");
    stepper.moveTo(200); // Rotate motor by 200 steps
  }

  lastButtonState = buttonState;

  stepper.run();
}
