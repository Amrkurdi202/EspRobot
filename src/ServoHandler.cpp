#include "ServoHandler.h"

ESP32ServoLite servo(SERVO_PIN, LEDC_CHANNEL_0);


void setupServo() {
  if (!servo.begin()) {
    Serial.println("Servo init failed");
    Serial.println("Servo init failed");
    while (1);
  }
}
