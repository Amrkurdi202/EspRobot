#ifndef SERVO_HANDLER_H
#define SERVO_HANDLER_H

#include "ESP32ServoLite.h"
#include "PinManger.h"

extern ESP32ServoLite servo;
void setupServo();
void setupSerial();

#endif
