#include <Arduino.h>
#include <configs.h>
#include <init_wifi.h>
#include <handle_sensor_data.h>
#include <handle_firebase_data.h>


void setup() {
  Serial.begin(115200);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  tone(BUZZER_PIN, 3000);
  delay(500);
  noTone(BUZZER_PIN);
  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);
  pinMode(LED_PIN, OUTPUT);
  strip.begin();  // Initialize the LED strip
  strip.show();
  for (int j = 0; j < sizeof(colors) / sizeof(colors[0]); j++) {
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, colors[j]);
    }
    strip.show();                 // Send the updated pixel colors to the strip
    digitalWrite(LED_PIN, HIGH);  // Turn off all LEDs initially
    delay(1000);                  // Wait for 1 second before changing colors
    digitalWrite(LED_PIN, LOW);
  }
  initWiFi();
  init_sensors();
  initFirebase();
  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, LOW);
  tone(BUZZER_PIN, 2000);
  delay(500);
  noTone(BUZZER_PIN);
  delay(500);
  tone(BUZZER_PIN, 5000);
  delay(500);
  noTone(BUZZER_PIN);
  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);
}

void loop() {
  txDataFirebase();
}