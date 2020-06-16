// Water meter
// Optical sensor is counting the liter wheel rotation.
// Both the digital and analog outputs of the sensor are monitored.
// MQTT messages for a Domoticz virtual sensor are created.
// An incremental counter for water is created on Domoticz.

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int waterCounter = 0; // counter for water pulses
int lastWaterCounter = 0; // previous counter for water pulses
int inputA0DigVal = 0; // digitalized analog input value
int lastInputA0DigVal = 0; // previous digitalized analog input value
int inputA0Val = 0; // analog input value
int lastInputA0Val = 0; // previous analog input value
int inputD1Val = 0; // digital input value
int lastInputD1Val = 0; // previous digital input value
const int wPulsePin =  5; // Pin D1, pulse input
const int analogPulse1 = 150;
const int analogPulse0 = 350;

// WiFi configuration
const char* ssid = "<your SSID>";
const char* password = "<your WiFi password>";
int wifitries = 0;
int connstatus;

IPAddress staticIP(192,168,42,81);
IPAddress gateway(192,168,42,1);
IPAddress subnet(255,255,255,0);

// MQTT configuration
const char* mqtt_server = "192.168.42.51";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* mqtt_topic = "domoticz/in";
char mqttbuffer[60];

WiFiClient espClient;
PubSubClient client(espClient);

// LED definitions
const int led = LED_BUILTIN;
const int led_on = LOW;
const int led_off = HIGH;

const int idx_water = 183; // Virtual sensor, counter incremental

// Handle recieved MQTT message, just print it
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Reconnect to MQTT broker
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("NodeMCUClient")) {
      Serial.println("connected");
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
  pinMode(led, OUTPUT);
  digitalWrite(led, led_off);
  pinMode(wPulsePin, INPUT);
  Serial.begin(115200);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.hostname("water-nodemcu");
  //WiFi.disconnect();
  Serial.println("Connect to network");
  Serial.printf("MAC address: %s\n", WiFi.macAddress().c_str());
  //delay(100);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  wifitries = 0;

  // Wait for WiFi connection
  Serial.println("Wait for WiFi connection");
  while ((connstatus = WiFi.status()) != WL_CONNECTED) {
    delay(600);
    digitalWrite(led, led_on);
    delay(400);
    Serial.printf(".");
    //Serial.printf("%d", connstatus);
    wifitries++;
    if (wifitries > 40) {
      Serial.println("");
      wifitries = 0;
    }
    digitalWrite(led, led_off);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  waterCounter = 0;
  lastWaterCounter = 0;
  inputA0Val = analogRead(A0); // Analog Values 0 to 1023
  if (inputA0Val < analogPulse1)
    lastInputA0DigVal = 1;
  if (inputA0Val > analogPulse0)
    lastInputA0DigVal = 0;
}

void loop() {
  inputA0Val = analogRead(A0); // Analog Values 0 to 1023
  inputD1Val = digitalRead(wPulsePin); // Digital value D1
  if (inputA0Val < analogPulse1)
    inputA0DigVal = 1;
  if (inputA0Val > analogPulse0)
    inputA0DigVal = 0;
  if ((inputA0DigVal == 1) && (lastInputA0DigVal == 0)) {
    waterCounter++;
  }
  lastInputA0DigVal = inputA0DigVal;
  //Serial.printf("Water liters: %d, D1: %d, A0: %d, A0Dig: %d\n", waterCounter, inputD1Val, inputA0Val// Water meter
// Optical sensor is counting the liter wheel rotation.
// Both the digital and analog outputs of the sensor are monitored.
// MQTT messages for a Domoticz virtual sensor are created.
// An incremental counter for water is created on Domoticz.

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int waterCounter = 0; // counter for water pulses
int lastWaterCounter = 0; // previous counter for water pulses
int inputA0DigVal = 0; // digitalized analog input value
int lastInputA0DigVal = 0; // previous digitalized analog input value
int inputA0Val = 0; // analog input value
int lastInputA0Val = 0; // previous analog input value
int inputD1Val = 0; // digital input value
int lastInputD1Val = 0; // previous digital input value
const int wPulsePin =  5; // Pin D1, pulse input
const int analogPulse1 = 150;
const int analogPulse0 = 350;

// WiFi configuration
const char* ssid = "CAMELOT2";
const char* password = "37sig&n%";
int wifitries = 0;
int connstatus;

IPAddress staticIP(192,168,42,81);
IPAddress gateway(192,168,42,1);
IPAddress subnet(255,255,255,0);

// MQTT configuration
const char* mqtt_server = "192.168.42.51";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* mqtt_topic = "domoticz/in";
char mqttbuffer[60];

WiFiClient espClient;
PubSubClient client(espClient);

// LED definitions
const int led = LED_BUILTIN;
const int led_on = LOW;
const int led_off = HIGH;

const int idx_water = 183; // Virtual sensor, counter incremental

// Handle recieved MQTT message, just print it
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Reconnect to MQTT broker
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("NodeMCUClient")) {
      Serial.println("connected");
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
  pinMode(led, OUTPUT);
  digitalWrite(led, led_off);
  pinMode(wPulsePin, INPUT);
  Serial.begin(115200);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.hostname("water-nodemcu");
  //WiFi.disconnect();
  Serial.println("Connect to network");
  Serial.printf("MAC address: %s\n", WiFi.macAddress().c_str());
  //delay(100);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  wifitries = 0;

  // Wait for WiFi connection
  Serial.println("Wait for WiFi connection");
  while ((connstatus = WiFi.status()) != WL_CONNECTED) {
    delay(600);
    digitalWrite(led, led_on);
    delay(400);
    Serial.printf(".");
    //Serial.printf("%d", connstatus);
    wifitries++;
    if (wifitries > 40) {
      Serial.println("");
      wifitries = 0;
    }
    digitalWrite(led, led_off);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  waterCounter = 0;
  lastWaterCounter = 0;
  inputA0Val = analogRead(A0); // Analog Values 0 to 1023
  if (inputA0Val < analogPulse1)
    lastInputA0DigVal = 1;
  if (inputA0Val > analogPulse0)
    lastInputA0DigVal = 0;
}

void loop() {
  inputA0Val = analogRead(A0); // Analog Values 0 to 1023
  inputD1Val = digitalRead(wPulsePin); // Digital value D1
  if (inputA0Val < analogPulse1)
    inputA0DigVal = 1;
  if (inputA0Val > analogPulse0)
    inputA0DigVal = 0;
  if ((inputA0DigVal == 1) && (lastInputA0DigVal == 0)) {
    waterCounter++;
  }
  lastInputA0DigVal = inputA0DigVal;
  //Serial.printf("Water liters: %d, D1: %d, A0: %d, A0Dig: %d\n", waterCounter, inputD1Val, inputA0Val, inputA0DigVal);
  if (waterCounter > lastWaterCounter) {
    lastWaterCounter = waterCounter;
    digitalWrite(led, led_on);
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    sprintf(mqttbuffer, "{ \"idx\" : %d, \"nvalue\" : 0, \"svalue\" : \"1\" }", idx_water);
    client.publish(mqtt_topic, mqttbuffer);
    Serial.println(mqttbuffer);
    digitalWrite(led, led_off);
    //Serial.printf("Water liters: %d, D1: %d, A0: %d\n", waterCounter, inputD1Val, inputA0Val);
  }
  
  delay(200);         // wait for 0.2 second
}, inputA0DigVal);
  if (waterCounter > lastWaterCounter) {
    lastWaterCounter = waterCounter;
    digitalWrite(led, led_on);
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    sprintf(mqttbuffer, "{ \"idx\" : %d, \"nvalue\" : 0, \"svalue\" : \"1\" }", idx_water);
    client.publish(mqtt_topic, mqttbuffer);
    Serial.println(mqttbuffer);
    digitalWrite(led, led_off);
    //Serial.printf("Water liters: %d, D1: %d, A0: %d\n", waterCounter, inputD1Val, inputA0Val);
  }
  
  delay(200);         // wait for 0.2 second
}
