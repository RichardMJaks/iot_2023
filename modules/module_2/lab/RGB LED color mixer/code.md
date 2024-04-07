```
#include <Arduino.h>

// Оголошення функції для кольорового світіння RGB діода
void rgb_single(int red_pin, int green_pin, int blue_pin, boolean common_anode) {
  // Ініціалізація пінів керування кольорами
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  // Задання кольорів (для спільного аноду, 1 - вмикнути, 0 - вимкнути)
  if (common_anode) {
    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin, HIGH);
    digitalWrite(blue_pin, HIGH);
  } else {
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
  }
}

// Встановлення пінів кольорів
const int redPin = D4;    // Пін для червоного кольору
const int greenPin = D3;  // Пін для зеленого кольору
const int bluePin = D2;   // Пін для синього кольору

void setup() {
  // Виклик функції для налаштування RGB діода
  rgb_single(redPin, greenPin, bluePin, true);
}

void loop() {
  // Вмикаємо червоний колір
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(500);  // Затримка на 2 секунди

  // Вмикаємо зелений колір
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  delay(500);  // Затримка на 2 секунди

  // Вмикаємо синій колір
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  delay(500);  // Затримка на 2 секунди
}
