#ifndef LST_DRIVERS_ADC_H_
#define LST_DRIVERS_ADC_H_

#include <Arduino.h>
#include <lib.h>

namespace lst {

const uint8_t kNumChannels = 10;

enum AdcChannel {
  ADC_MULTIPLEX_1 = 0,
  ADC_POT_1,
  ADC_POT_2,
  ADC_CHANNEL_LAST
};

class Adc {
 public:
  Adc() { }
  ~Adc() { }
  
  void Init();
  void Read();
  inline uint16_t value(uint8_t channel) const { return values_[channel]; } // 10 bit value
  inline uint8_t value8(uint8_t channel) const { return values_[channel] >> 2; } // 8 bit value
  inline float float_value(uint8_t channel) const {
    return static_cast<float>(values_[channel] >> 2) / 256.0f;
  }
 
 private:
  uint16_t values_[kNumChannels];
  uint8_t current_multiplex_channel;
  uint8_t current_adc_channel;

  uint16_t audio_divider_;
  DISALLOW_COPY_AND_ASSIGN(Adc);
};

}  // namespace lst

#endif  // LST_DRIVERS_ADC_H_
