#include <Arduino.h>
#include "ServoHandler.h"

ESP32ServoLite servo(SERVO_PIN, LEDC_CHANNEL_0);

void setupSerial() {
  Serial.begin(115200);
}

void setupServo() {
  if (!servo.begin()) {
    Serial.println("Servo init failed");
    while (1);
  }
}
