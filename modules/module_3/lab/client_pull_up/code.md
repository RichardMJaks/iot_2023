#include <ESP8266WiFi.h>

const char* wifiSSID = "iotempire-slavenet"; // Ваш SSID WiFi
const char* wifiPassword = "iotempire"; // Ваш пароль WiFi

const char* serverIP = "10.42.0.79"; // IP адреса ESP8266 з веб-сервером

WiFiClient client;

const int buttonPin = D2; // Виберіть пін, до якого підключено кнопку
int buttonState;         // Поточний стан кнопки
int lastButtonState = HIGH; // Попередній стан кнопки, початково високий, тому що кнопка підтягнута до VCC
int colorMode = 0; // 0 - вимкнено, 1 - зелений, 2 - синій, 3 - червоний

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
}

void loop() {
  // Читаємо стан кнопки
  buttonState = digitalRead(buttonPin);

  // Виводимо стан кнопки тільки якщо він змінився
  if (buttonState != lastButtonState) {
    delay(50); // Проста антидребезгова затримка
    // Якщо кнопка відпущена
    if (buttonState == HIGH) {
      toggleLEDonServer();
    }

    lastButtonState = buttonState; // Зберігаємо поточний стан кнопки
  }
}

void toggleLEDonServer() {
  String path;
  switch (colorMode) {
    case 1:
      path = "/green";
      break;
    case 2:
      path = "/blue";
      break;
    case 3:
      path = "/red";
      break;
    default:
      path = "/off"; // Використовуйте "/off" для вимкнення
      break;
  }

  if (client.connect(serverIP, 80)) {
    client.println("GET " + path + " HTTP/1.1");
    client.println("Host: " + String(serverIP));
    client.println("Connection: close");
    client.println(); // Порожній рядок важливий для завершення HTTP запиту
    Serial.println("Запит відправлено: " + path);
  } else {
    Serial.println("Помилка підключення до сервера");
  }

  colorMode = (colorMode + 1) % 4; // Перемикайте на наступний колір або вимкніть

  // Дайте серверу час на обробку запиту
  delay(1000);
}