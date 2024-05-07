#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>

// WiFi settings
const char* ssid = "iotempire-slavenet";  // Your WiFi SSID
const char* password = "iotempire";       // Your WiFi password

// MQTT server settings
const char* mqttServer = "192.168.12.1";   // IP address of your MQTT server
const int mqttPort = 1883;
const char* mqttUser = "";                // MQTT username (leave empty if not used)
const char* mqttPassword = "";            // MQTT password (leave empty if not used)

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void reconnect_mqtt() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
      // Publish a message to indicate the system has rebooted
      client.publish("lora/status", "REBOOTED");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();  // Connect to WiFi
  
  client.setServer(mqttServer, mqttPort); // Connect to MQTT
  reconnect_mqtt();

  LoRa.setPins(D4, D3, D2); // Set LoRa module pins
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    String message = "";

    while (LoRa.available()) {
      char receivedChar = (char)LoRa.read();
      message += receivedChar;
      Serial.print(receivedChar);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    // Publish the message to MQTT
    if (!message.isEmpty()) {
      client.publish("lora/messages", message.c_str());
    }
  }
}
