#include <FirebaseClient.h>

#define API_KEY "API_KEY"
#define USER_EMAIL "USER_EMAIL"
#define USER_PASSWORD "USER_PASSWORD"
#define DATABASE_URL "DATABASE_URL"
void asyncCB(AsyncResult &aResult);
void printResult(AsyncResult &aResult);
DefaultNetwork network;  // initilize with boolean parameter to enable/disable network reconnection
UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD);
FirebaseApp app;

#include <WiFiClientSecure.h>
WiFiClientSecure ssl_client1, ssl_client2;

using AsyncClient = AsyncClientClass;

AsyncClient aClient(ssl_client1, getNetwork(network)), aClient2(ssl_client2, getNetwork(network));

RealtimeDatabase Database;

unsigned long ms = 0;

void initFirebase() {

  // Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

  Serial.println("Initializing app...");

  ssl_client1.setInsecure();
  ssl_client2.setInsecure();


  initializeApp(aClient2, app, getAuth(user_auth), asyncCB, "authTask");

  // Binding the FirebaseApp for authentication handler.
  // To unbind, use Database.resetApp();
  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);
  Database.setSSEFilters("get,put,patch,keep-alive,cancel,auth_revoked");
  Database.get(aClient, "/mosque1/state", asyncCB, true, "streamTask");
}

void txDataFirebase() {
  app.loop();

  Database.loop();

  if (millis() - ms > 5000 && app.ready()) {
    ms = millis();
    JsonWriter writer;
    object_t jsonflow, jsonlight, jsonmotion, jsontemp, obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8;
    writer.create(obj1, "0", sensorsReadings.flow);
    writer.create(obj2, "0", sensorsReadings.light);
    writer.create(obj3, "0", sensorsReadings.motion);
    writer.create(obj4, "0", sensorsReadings.temp);
    fetch_sensors_data();
    writer.create(obj5, "1", sensorsReadings.flow);
    writer.create(obj6, "1", sensorsReadings.light);
    writer.create(obj7, "1", sensorsReadings.motion);
    writer.create(obj8, "1", sensorsReadings.temp);
    writer.join(jsonflow, 2, obj1, obj5);
    writer.join(jsonlight, 2, obj2, obj6);
    writer.join(jsonmotion, 2, obj3, obj7);
    writer.join(jsontemp, 2, obj4, obj8);
    analogWrite(R_PIN, 0);
    analogWrite(G_PIN, 255);
    analogWrite(B_PIN, 255);
    delay(200);
    analogWrite(R_PIN, 255);
    analogWrite(G_PIN, 0);
    analogWrite(B_PIN, 255);
    delay(200);
    analogWrite(R_PIN, 255);
    analogWrite(G_PIN, 255);
    analogWrite(B_PIN, 0);
    delay(200);
    analogWrite(R_PIN, 255);
    analogWrite(G_PIN, 255);
    analogWrite(B_PIN, 255);

    Database.update(aClient2, "/mosque1/sensors/flow", jsonflow, asyncCB, "updateTask");
    Database.update(aClient2, "/mosque1/sensors/light", jsonlight, asyncCB, "updateTask");
    Database.update(aClient2, "/mosque1/sensors/motion", jsonmotion, asyncCB, "updateTask");
    Database.update(aClient2, "/mosque1/sensors/temp", jsontemp, asyncCB, "updateTask");
    delay(1000);
  }
}

void asyncCB(AsyncResult &aResult) {
  printResult(aResult);
}

void printResult(AsyncResult &aResult) {
  if (aResult.isEvent()) {
    Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
  }

  if (aResult.isDebug()) {
    Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
  }

  if (aResult.isError()) {
    Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
  }

  if (aResult.available()) {
    RealtimeDatabaseResult &RTDB = aResult.to<RealtimeDatabaseResult>();
    if (RTDB.isStream()) {
      Serial.println("----------------------------");
      
      if (RTDB.to<String>() == "open") {
          for (int i = 0; i < LED_COUNT; i++) {
            strip.setPixelColor(i, strip.Color(0, 255, 0));
          }
          strip.show();                 // Send the updated pixel colors to the strip
          digitalWrite(LED_PIN, HIGH);  // Turn off all LEDs initially
          delay(1000);                  // Wait for 1 second before changing colors
          digitalWrite(LED_PIN, LOW);
        }else{
          for (int i = 0; i < LED_COUNT; i++) {
            strip.setPixelColor(i, strip.Color(255, 0, 0));
          }
          strip.show();                 // Send the updated pixel colors to the strip
          digitalWrite(LED_PIN, HIGH);  // Turn off all LEDs initially
          delay(1000);                  // Wait for 1 second before changing colors
          digitalWrite(LED_PIN, LOW);

        }

      Firebase.printf("data: %s\n", RTDB.to<const char *>());
    }
  }
}