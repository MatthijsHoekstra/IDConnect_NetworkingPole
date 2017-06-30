#include <UIPEthernet.h>
#include <PubSubClient.h>

#include <Wire.h>

#define CLIENT_ID       "Pole_0"
#define TOPIC           "ID"

uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

IPAddress mqttServer(10, 0, 0, 1);

byte ip[] = {10, 0, 0, 2};

EthernetClient ethClient;
PubSubClient mqttClient;

long previousMillis;

int statusSlave = 0; // 0 - MQTT failed // 1 - Normal

void setup() {

  // setup serial communication
  //Serial.begin(9600);

  // setup ethernet communication using DHCP
  Ethernet.begin(mac, ip);

  //  Serial.println(F("Ethernet configured via DHCP"));
  //  Serial.print("IP address: ");
  //  Serial.println(Ethernet.localIP());
  //  Serial.println();

  // setup mqtt client
  mqttClient.setClient(ethClient);
  mqttClient.setServer(mqttServer, 1883);
  Serial.println(F("MQTT client configured"));

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {

  mqttClient.loop();
}

void sendData() {

  char msgBuffer[20];

  if (mqttClient.connect(CLIENT_ID)) {

    mqttClient.publish(TOPIC, dtostrf('1', 6, 2, msgBuffer));
  }
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
   // Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
}

