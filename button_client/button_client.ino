#include <ESP8266WiFi.h>

const char* wifiSSID = "iotempire-slavenet"; // Ваш SSID WiFi
const char* wifiPassword = "iotempire"; // Ваш пароль WiFi

const char* serverIP = "10.42.0.27"; // IP адреса ESP8266 з веб-сервером

WiFiClient client;

const int buttonPin = D2; // Виберіть пін, до якого підключено кнопку
int buttonState;         // Поточний стан кнопки
int lastButtonState = HIGH; // Попередній стан кнопки, початково високий, тому що кнопка підтягнута до VCC
bool lastLEDState = false; // Початковий стан світлодіода (false = вимкнено)


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  
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
    // Якщо кнопка відпущена
    if (buttonState == HIGH && lastButtonState == LOW) {
      Serial.println("Кнопка відпущена");
      toggleLEDonServer();
    }

    lastButtonState = buttonState; // Зберігаємо поточний стан кнопки
  }

  delay(200); // Затримка для стабілізації читання
}

void toggleLEDonServer() {
  String path = lastLEDState ? "/off" : "/on";

  if (client.connect(serverIP, 80)) {
    client.println("GET " + path + " HTTP/1.1");
    client.println("Host: " + String(serverIP));
    client.println("Connection: close");
    client.println(); // Порожній рядок важливий для завершення HTTP запиту
    lastLEDState = !lastLEDState;
    Serial.println("Запит відправлено: " + path);
  } else {
    Serial.println("Помилка підключення до сервера");
  }

  // Дайте серверу час на обробку запиту
  delay(1000);
}