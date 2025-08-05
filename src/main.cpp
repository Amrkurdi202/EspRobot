#include<Arduino.h>
#include "PinManger.h"
#include "SerialManger.h"
#include "WiFiHandler.h"
#include "MotorHandler.h"
#include "ServoHandler.h"

void setup() {
  setupPins();
  setupSerial();
  setupServo();
  setupWiFi();
  setupUDP();
}

void loop() {
  loopUDP();
  checkVibration();
}
