#include <Arduino.h>

// Pins for the RGB LED
const int redPin = D4;
const int greenPin = D3;
const int bluePin = D2;

// Pin for the button
const int buttonPin = D5;

// Variable to store the current color mode
int colorMode = 0;

// Variable to debounce the button press
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Variable to store the last button state
int lastButtonState = HIGH; // Assume button starts not pressed

void setup() {
  // Initialize the LED pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize the button pin as an input with the internal pull-up resistor enabled
  pinMode(buttonPin, INPUT_PULLUP);

  // Initial color off
  setColor(LOW, LOW, LOW);
}

void loop() {
  // Read the state of the button
  int buttonState = digitalRead(buttonPin);

  // Check for button release (transition from LOW to HIGH)
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Check for debounce to avoid detecting false releases
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // Change the color mode
      colorMode = (colorMode + 1) % 4;

      // Update the color based on the mode
      switch (colorMode) {
        case 0:
          setColor(LOW, LOW, LOW); // Off
          break;
        case 1:
          setColor(HIGH, LOW, LOW); // Red
          break;
        case 2:
          setColor(LOW, HIGH, LOW); // Green
          break;
        case 3:
          setColor(LOW, LOW, HIGH); // Blue
          break;
      }

      // Reset the debounce timer
      lastDebounceTime = millis();
    }
  }

  // Update the last button state
  lastButtonState = buttonState;
}

void setColor(boolean red, boolean green, boolean blue) {
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(bluePin, blue);
}