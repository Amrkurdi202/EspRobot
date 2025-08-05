#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#include "ESP32MX1508.h"

void handleJoystick(byte dir);
void setLaser(byte value);
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();
void checkVibration();

#endif
