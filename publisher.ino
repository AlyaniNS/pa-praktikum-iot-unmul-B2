// Library
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

// Pin yang digunakan
#define red D3
#define yellow D4
#define green D5
#define button D7

// Konfigurasi WiFi
#define WIFI_SSID "Universitas Mulawarman"
#define WIFI_PASSWORD ""

// Konfigurasi Broker MQTT
#define MQTT_SERVER "broker.hivemq.com"
int MQTT_PORT = 1883;
#define MQTT_TOPIC "iot_unmul/red_light"

// Buat instance WiFiClient dan PubSubClient
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void handleSave() {
  String mqttServer = server.arg("mqtt_server");
  String mqttPort = server.arg("mqtt_port");
  String mqttTopic = server.arg("mqtt_topic");

  mqttServer.toCharArray(MQTT_SERVER, sizeof(MQTT_SERVER));
  MQTT_PORT = mqttPort.toInt();
  mqttTopic.toCharArray(MQTT_TOPIC, sizeof(MQTT_TOPIC));
}

void setup() {
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);

  connectToWiFi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  Serial.println("Menyambungkan ke " + WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  server.handleClient();

  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

bool nilaiB = digitalRead(button);

  if (digitalRead(button) == HIGH) {
    delay(15);  // software debounce
    if (digitalRead(button) == HIGH) {
      Serial.println("Tombol sudah ditekan!");
      changeLights();
      publishToMQTT(button);
      delay(1000);
    }
  }
}

void changeLights() {
  // green off, yellow on for 3 seconds
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  delay(3000);

  // turn off yellow, then turn green on for 6 seconds
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  delay(6000);

  // green and yellow on for 2 seconds (red is already on though)
  digitalWrite(green, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  delay(2000);

  // turn off green and yellow, then turn on red
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(3000);
}

void publishToMQTT(bool nilaiB) {
  if (mqttClient.publish(MQTT_TOPIC, String(nilaiB).c_str())) {
    Serial.println("Published to MQTT: " + String(nilaiB));
  } else {
    Serial.println("Failed to publish to MQTT");
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Handle MQTT messages if needed
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    String clientId = "ESP8266Client-" + String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
