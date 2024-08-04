#include <ESP8266WiFi.h>

// Insert your network credentials
#define WIFI_SSID "Abdulrahman"
#define WIFI_PASSWORD "12345678"
// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to WiFi ..");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  
  Serial.println();
  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());
}
