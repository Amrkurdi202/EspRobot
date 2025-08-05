#include <Arduino.h>
#include "MotorHandler.h"
#include "PinManger.h"


MX1508 motor1(MOTOR1_A, MOTOR1_B, LEDC_CHANNEL_1, LEDC_CHANNEL_2, 8, 5000);
MX1508 motor2(MOTOR2_A, MOTOR2_B, LEDC_CHANNEL_3, LEDC_CHANNEL_4, 8, 5000);

int val = 0;
float speed_factor = 1;


void handleJoystick(byte dir) {
  switch (dir) {
    case 1: turnRight(); break;
    case 2: moveBackward(); break;
    case 3: turnLeft(); break;
    case 4: moveForward(); break;
    case 5: motor1.motorRev(255); motor2.motorBrake(); break;
    case 6: motor1.motorBrake(); motor2.motorRev(255); break;
    case 7: motor1.motorBrake(); motor2.motorGo(255); break;
    case 8: motor1.motorGo(255); motor2.motorBrake(); break;
    default: stopMotors(); break;
  }
}

void setLaser(byte value) {
  digitalWrite(LASER_PIN, value > 90 ? HIGH : LOW);
}

void moveForward() {
  long speed = 255 * speed_factor;
  motor1.motorGo(speed);
  motor2.motorGo(speed);
}

void moveBackward() {
  long speed = 255 * speed_factor;
  motor1.motorRev(speed);
  motor2.motorRev(speed);
}

void turnLeft() {
  long speed = 255 * speed_factor;
  motor1.motorRev(speed);
  motor2.motorGo(speed);
}

void turnRight() {
  long speed = 255 * speed_factor;
  motor1.motorGo(speed);
  motor2.motorRev(speed);
}

void stopMotors() {
  motor1.motorBrake();
  motor2.motorBrake();
}

void checkVibration() {
  val = digitalRead(VIB_PIN);
  digitalWrite(LED_PIN, val == HIGH ? HIGH : LOW);
}
