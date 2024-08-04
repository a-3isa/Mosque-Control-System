#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

int lightInit;  // initial value

volatile int pulseCount = 0;
float flowRate = 0.0;
const int pulsePerLiter = 5880 ; // Number of pulses per liter (change based on your sensor's spec)


void  pulseCounter() {
  pulseCount++;
}

void init_sensors() {
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(FLOW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseCounter, RISING);
}

void fetch_sensors_data() {
  sensorsReadings.motion =  digitalRead(PIR_PIN); 
  sensorsReadings.light =  analogRead(LIGHT_PIN);
  int adcValue = analogRead(TEMP_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;
  sensorsReadings.temp = (voltage - 0.3) * 100.0;
  sensorsReadings.flow = (pulseCount / float(pulsePerLiter)) * (60000.0 / 5000);
  pulseCount = 0;
}