#ifndef LST_UI_H_
#define LST_UI_H_

#include <Arduino.h>
#include <lib.h>
#include <drivers/system_clock.h>
#include <drivers/adc.h>
#include <drivers/switches.h>

namespace lst {

const uint8_t kFinePotDivider = 2;
const uint8_t kNumPots = 2;

class App;

enum FeatureMode {
  ADC_DAC = 0, 
  FUNCTION_LAST
};

enum UiMode {
  UI_MODE_SPLASH,
  UI_MODE_NORMAL,
  UI_MODE_SETTINGS,
  UI_MODE_SECRET
};

class Ui {
 public:
  Ui() { }
  ~Ui() { }
  
  void Init(Adc* adc, App* app);
  //void Init();
  void Poll();
  void DoEvents();
  void FlushEvents();

  uint16_t coarse(uint8_t channel) {
    return pot_coarse_value_[channel];
  }

  inline FeatureMode feat_mode() const { return feat_mode_; }
  inline UiMode mode() const { return mode_; }

  uint8_t getSymbol();
  uint8_t getLedSymbol();

 private:
  void OnSwitchPressed();
  void OnSwitchReleased(uint8_t id, int32_t t);
  void OnPotChanged();
  void OnPressureReleased(uint8_t id, int32_t t);

  uint16_t pot_value_[kNumChannels];
  uint16_t pot_filtered_value_[kNumChannels];
  uint16_t pot_coarse_value_[kNumChannels];

  // 2nd row of plates and 2 buttons
  uint32_t press_time_[kNumSwitches];
  bool detect_very_long_press_[kNumSwitches];
  bool catchup_state_[kNumSwitches];
  bool pressed[kNumSwitches];

  int32_t animation_counter_;
  uint8_t blink_counter_;
  int8_t ignore_releases_;
  bool switchState;

  Switches switches_;
  Adc *adc_;
  App* app_;

  UiMode mode_;
  FeatureMode feat_mode_, last_feature_mode;
  
  uint8_t led_state;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

}  // namespace lst

#endif  // LST_UI_H_
