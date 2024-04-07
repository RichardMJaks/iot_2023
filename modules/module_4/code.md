```
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Your WiFi settings
const char* ssid = "iotempire-slavenet"; // Your WiFi SSID
const char* password = "iotempire"; // Your WiFi password

// MQTT server settings
const char* mqttServer = "10.42.0.176"; // IP address of your MQTT server
const int mqttPort = 1883;
const char* mqttUser = ""; // Leave empty if not needed
const char* mqttPassword = ""; // Leave empty if not needed

WiFiClient espClient;
PubSubClient client(espClient);

int inputPin = D2; // Pin connected to the motion sensor
int lastMotionState = LOW; // Stores the last motion sensor state

void setup() {
  Serial.begin(115200);
  pinMode(inputPin, INPUT);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ArduinoClient", mqttUser, mqttPassword)) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("Connecting error, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  int motion = digitalRead(inputPin);
  
  // If motion detected and last state was no motion
  if (motion == HIGH && lastMotionState == LOW) {
    Serial.println("Motion Detected!");
    client.publish("home/room/motion", "Motion Detected!");
    lastMotionState = HIGH; // Update last motion sensor state
  }
  // If no motion detected and last state was motion detected
  else if (motion == LOW && lastMotionState == HIGH) {
    Serial.println("No Motion Detected!");
    client.publish("home/room/motion", "No Motion Detected!");
    lastMotionState = LOW; // Update last motion sensor state
  }
  
  delay(100); // Delay to prevent too frequent updates
}
