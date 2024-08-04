#define LED_PIN 21  // Digital pin connected to the LED strip
#define LED_COUNT 8   // Number of LEDs in the strip
#define SERVO_PIN 13  // Digital pin connected to the Servo 
#define PIR_PIN 14  // Digital pin connected to the PIR motion sensor 
#define LIGHT_PIN 34  // Digital pin connected to the LDR 
#define TEMP_PIN 35  // Digital pin connected to the temperature sensor 
#define FLOW_PIN 27  // Digital pin connected to the flow sensor 
#define BUZZER_PIN 26  // Digital pin connected to the Buzzer 
#define R_PIN 19  // Digital pin connected to the R in RGB led 
#define G_PIN 23  // Digital pin connected to the G in RGB led 
#define B_PIN 18  // Digital pin connected to the B in RGB led 
#define RF_TX 16    // Digital pin connected to the TX pin in RF module 
#define RF_RX 17  // Digital pin connected to the RX pin in RF module
#define RF_CON 39  // Digital pin connected to the control pin in RF module
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t colors[] = {
  strip.Color(255, 0, 0),     // Red
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 0, 255),     // Blue
  strip.Color(255, 255, 0), // White
};

struct readings{
  double motion,flow,light,temp;
  
};
readings sensorsReadings;

