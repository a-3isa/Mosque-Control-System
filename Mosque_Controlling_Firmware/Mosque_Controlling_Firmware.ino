#include "init_wifi.h"
const int fanRelayPin = 14;    // Change this to your chosen pin
const int led1Relay2Pin = 13;  // Change this to your chosen pin
const int led2Relay3Pin = 12;

#include "handle_firebase_data.h"



void setup() {

  Serial.begin(115200);
  initWiFi();
  firebase_init();
  pinMode(fanRelayPin, OUTPUT);
  pinMode(led1Relay2Pin, OUTPUT);
  pinMode(led2Relay3Pin, OUTPUT);
  digitalWrite(fanRelayPin, LOW);
  digitalWrite(led1Relay2Pin, LOW);
  digitalWrite(led2Relay3Pin, LOW);
}

void loop() {
  firebase_fetech();
}