#include "ESP32MX1508.h"

MX1508::MX1508(uint8_t pinIN1, uint8_t pinIN2, ledc_channel_t channelIN1, ledc_channel_t channelIN2, uint8_t resolution, long freq){
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _chIN1 = channelIN1;
  _chIN2 = channelIN2;
  _res = resolution;
  _freq = freq;

  ledc_timer_config_t timer_conf = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = (ledc_timer_bit_t)_res,
    .timer_num = LEDC_TIMER_1,
    .freq_hz = _freq,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&timer_conf);

  ledc_channel_config_t chan1 = {
    .gpio_num = _pinIN1,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = _chIN1,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_1,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&chan1);

  ledc_channel_config_t chan2 = {
    .gpio_num = _pinIN2,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = _chIN2,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_1,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&chan2);

  if (_res == 8) _maxpwm = 255;
  if (_res == 12) _maxpwm = 4095;
  if (_res == 16) _maxpwm = 65535;
}

void MX1508::stopMotor() {
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN1, 0);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN1);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN2, 0);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN2);
}

void MX1508::motorStop() {
  stopMotor();
}

void MX1508::motorBrake() {
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN1, _maxpwm);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN1);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN2, _maxpwm);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN2);
}

void MX1508::motorGo(long pwmSpeed) {
  _pwmVal = pwmSpeed;
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN1, _pwmVal);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN1);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN2, 0);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN2);
}

void MX1508::motorRev(long pwmSpeed) {
  _pwmVal = pwmSpeed;
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN1, 0);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN1);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, _chIN2, _pwmVal);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, _chIN2);
}
