#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* ssid = "Universitas Mulawarman";
const char* password = ""; 
const char* mqtt_server = "broker.hivemq.com"; 

#define triggerPin  D8
#define echoPin     D7
#define BuzzerPin D1

WiFiClient wifiClient;
PubSubClient client(wifiClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() { 
  delay(10);
  Serial.println();
  Serial.print("Connecting to "); 
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan diterima dari [");
  Serial.print(topic);
  Serial.print("] ");
  String data = ""; 
  for (int i = 0; i < length; i++) { 
    Serial.println((char)payload[i]);
    data += (char)payload[i]; 
  }
  client.subscribe("iot_unmul/red_light"); 
  if ((char)payload[0] == 1) {
    Serial.println("Tombol ditekan!");
    long duration, jarak;
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(3); 
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(3); 
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    jarak = (duration/2) / 29.1;
    Serial.println(" cm");
    Serial.println("Jarak: " + String(jarak) + " cm");
    delay(1000); 
  }
   int jarak = data.toInt(); 
  if (jarak < 30) { 
    tone(BuzzerPin,1000,2000);
  } else {
    noTone(BuzzerPin);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("iot_unmul/red_light");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}
void setup() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(BuzzerPin, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883); 
    client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
