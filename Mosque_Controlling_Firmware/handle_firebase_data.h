#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
// Insert Firebase project API Key
#define API_KEY "API_KEY"
// User Email and password that already registerd or added in your project.
#define USER_EMAIL "USER_EMAIL"
#define USER_PASSWORD "USER_PASSWORD"
#define DATABASE_URL "DATABASE_URL"

// Define Firebase objects
FirebaseData fbdoFan;
FirebaseData fbdoLed1;
FirebaseData fbdoLed2;
FirebaseAuth auth;
FirebaseConfig config;



void firebase_init() {
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdoFan.setResponseSize(4096);
  fbdoLed1.setResponseSize(4096);
  fbdoLed2.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);
  Serial.println();
  Serial.print("Connected to Firebase");
}

void firebase_fetech() {
  Firebase.RTDB.getBool(&fbdoLed1, "/mosque1/actuators/led1");

  if(fbdoLed1.boolData()){
    digitalWrite(led1Relay2Pin, HIGH);
  } else {
    digitalWrite(led1Relay2Pin, LOW);

  }


  Firebase.RTDB.getBool(&fbdoLed2, "/mosque1/actuators/led2");

  if(fbdoLed2.boolData()){
    digitalWrite(led2Relay3Pin, HIGH);
  } else {
    digitalWrite(led2Relay3Pin, LOW);

  }

  Firebase.RTDB.getBool(&fbdoFan, "/mosque1/actuators/fan");

  if(fbdoFan.boolData()){
    digitalWrite(fanRelayPin, HIGH);
  } else {
    digitalWrite(fanRelayPin, LOW);

  }

  delay(100);





}