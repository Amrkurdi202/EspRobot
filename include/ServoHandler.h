#ifndef SERVO_HANDLER_H
#define SERVO_HANDLER_H

#include <Arduino.h>
#include "SerialManger.h"
#include "ESP32ServoLite.h"
#include "PinManger.h"

extern ESP32ServoLite servo;
void setupServo();

#endif
