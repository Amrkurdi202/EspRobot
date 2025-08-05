#include <Arduino.h>
#include "PinManger.h"


void setupPins() {
  pinMode(VIB_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LASER_PIN, OUTPUT);
}