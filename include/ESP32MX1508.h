#ifndef ESP32MX1508_H
#define ESP32MX1508_H

#include <Arduino.h>
#include "driver/ledc.h"

class MX1508 {
public:
  MX1508(uint8_t pinIN1, uint8_t pinIN2, ledc_channel_t channelIN1, ledc_channel_t channelIN2, uint8_t resolution, long freq);

  void motorGo(long pwmSpeed);
  void motorRev(long pwmSpeed);
  void motorStop();
  void stopMotor();
  void motorBrake();

private:
  uint8_t _pinIN1;
  uint8_t _pinIN2;
  ledc_channel_t _chIN1;
  ledc_channel_t _chIN2;
  uint8_t _res;
  long _freq;
  long _pwmVal;
  long _maxpwm;
};

#endif
