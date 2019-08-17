#include <ui.h>
#include <math.h>
#include <app/app.h>
#include <resources.h>

namespace lst {

using namespace std;
using namespace lib;

const int32_t kLongPressDuration = 500;
const int32_t kVeryLongPressDuration = 2000;
const int32_t kPotMoveThreshold = 1; 
const uint16_t kCatchupThreshold = 1 << 10;

void Ui::Init(Adc* adc, App* app) {
  adc_ = adc;
  app_ = app;
  switches_.Init();

  mode_ = UI_MODE_SPLASH;

  animation_counter_ = 0;
  blink_counter_ = 0;
  ignore_releases_ = 0;
  led_state = 0;
  
  switchState = false;
  for (uint8_t i = 0; i < kNumSwitches; ++i) {
    pressed[i] = false;
    press_time_[i] = 0;
    detect_very_long_press_[i] = false;
  }
}

void Ui::Poll() {
  // switches_.Debounce();

  for (uint8_t i = 0; i < kNumSwitches; i++) {
    switchState = digitalRead(PB1);
    if (switchState && !pressed[i]) { // justPressed
      press_time_[i] = system_clock.milliseconds();
      detect_very_long_press_[i] = false;
      pressed[i] = true;
    }

    if (!switchState && press_time_[i]) {
      int32_t pressed_time = system_clock.milliseconds() - press_time_[i];
      
      if (!detect_very_long_press_[i]) {
        if (pressed_time > kLongPressDuration) { // longPressed
          OnSwitchReleased(i, pressed_time);
          detect_very_long_press_[i] = true;
        }
      } else {
        if (pressed_time > kVeryLongPressDuration) { // veryLongPressed
          OnSwitchReleased(i, pressed_time);
          detect_very_long_press_[i] = false;
          press_time_[i] = 0;
          pressed[i] = false;
        }
      }
    }
    //if ((switchState == 0x01) && press_time_[i] != 0 && !detect_very_long_press_[i]) { 
    if ((!switchState) && press_time_[i] != 0 && !detect_very_long_press_[i]) { // pressRelease
      OnSwitchReleased(i, system_clock.milliseconds() - press_time_[i] + 1);
      press_time_[i] = 0;
      detect_very_long_press_[i] = false;
      pressed[i] = false;
    }
  }

  if (mode_ == UI_MODE_SPLASH) {
    if (animation_counter_ == 256) {
        animation_counter_ = 0;
      	mode_ = UI_MODE_NORMAL;
    }
    animation_counter_++;
  } else {
    // filter the pot values and emit events when changed
    for (uint8_t i = 0; i < kNumChannels; ++i) {
      uint16_t adc_value = adc_->value(i);
      int32_t value = (31 * pot_filtered_value_[i] + adc_value) >> 5;
      pot_filtered_value_[i] = value;
      int32_t current_value = static_cast<int32_t>(pot_value_[i]);
      if ((value >= current_value + kPotMoveThreshold) || (value <= current_value - kPotMoveThreshold)) {
        //if (abs(value - pot_coarse_value_[i]) < kCatchupThreshold) {
          pot_coarse_value_[i] = value;
          //catchup_state_[i] = false;
        // }
        pot_value_[i] = value;
      }
    }
  }

  //display_.Tick();
}

void Ui::OnSwitchPressed() {
  //
}


void Ui::OnSwitchReleased(uint8_t id, int32_t t) {
  if (t > kVeryLongPressDuration) {
    //
  } else if (t > kLongPressDuration) {  
    // 
    
  } else {
    
  }
}

uint8_t Ui::getLedSymbol() {
  // paint leds
//   switch (mode_) {
//     case UI_MODE_SPLASH:
//       return leds_.animate(); 
//     case UI_MODE_SECRET:
//       break;
//     case UI_MODE_NORMAL:
//       return app_->getStep();
//     case UI_MODE_GATE:
//       return (0b11111111 & ~(app_->getGatesBinary()));
//     case UI_MODE_SETTINGS:
//       return (0b11111111 & ~(led_state));
//     case UI_MODE_SEQUENCER:
//       return (0b11111111 & ~(led_state));
//     case UI_MODE_KEYBOARD:
//       return (0b11111111 & ~(led_state));
//     case UI_MODE_ARP:
//       return app_->getStep();
//     case UI_MODE_SCALE:
//       return (0b11111111 & ~(led_state));
//   }
   return 0;
}

}  // namespace lst
