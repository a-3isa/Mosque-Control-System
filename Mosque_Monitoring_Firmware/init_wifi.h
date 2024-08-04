#include <WiFi.h>
// Insert your network credentials
#define WIFI_SSID "Abdulrahman"
#define WIFI_PASSWORD "12345678"
// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}
