#include "WiFiHandler.h"
#include "MotorHandler.h"
#include "ServoHandler.h"
#include "PinManger.h"

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
