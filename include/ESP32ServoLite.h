#ifndef ESP32_SERVO_LITE_H
#define ESP32_SERVO_LITE_H

#include "Arduino.h"
#include "driver/ledc.h"

class ESP32ServoLite {
public:
  ESP32ServoLite(int gpio, ledc_channel_t channel, ledc_timer_t timer = LEDC_TIMER_0, ledc_timer_bit_t resolution = LEDC_TIMER_13_BIT);
  bool begin();
  void write(int angle);

private:
  int _gpio;
  ledc_channel_t _channel;
  ledc_timer_t _timer;
  ledc_timer_bit_t _resolution;
  ledc_mode_t _mode = LEDC_LOW_SPEED_MODE;
  uint32_t _freq = 50;
};

#endif
