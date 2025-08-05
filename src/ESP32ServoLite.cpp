#include "ESP32ServoLite.h"

ESP32ServoLite::ESP32ServoLite(int gpio, ledc_channel_t channel, ledc_timer_t timer, ledc_timer_bit_t resolution)
  : _gpio(gpio), _channel(channel), _timer(timer), _resolution(resolution) {}

bool ESP32ServoLite::begin() {
  ledc_timer_config_t timer_conf = {
    .speed_mode = _mode,
    .duty_resolution = _resolution,
    .timer_num = _timer,
    .freq_hz = _freq,
    .clk_cfg = LEDC_AUTO_CLK
  };

  if (ledc_timer_config(&timer_conf) != ESP_OK) return false;

  ledc_channel_config_t channel_conf = {
    .gpio_num = _gpio,
    .speed_mode = _mode,
    .channel = _channel,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = _timer,
    .duty = 0,
    .hpoint = 0
  };

  return ledc_channel_config(&channel_conf) == ESP_OK;
}

void ESP32ServoLite::write(int angle) {
  int us = map(angle, 0, 180, 500, 2500);
  uint32_t maxDuty = (1 << _resolution) - 1;
  uint32_t duty = (us * maxDuty) / 20000;

  ledc_set_duty(_mode, _channel, duty);
  ledc_update_duty(_mode, _channel);
}
