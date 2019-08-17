#ifndef LST_DRIVERS_SWITCHES_H_
#define LST_DRIVERS_SWITCHES_H_

#include <Arduino.h>

namespace lst {

const uint8_t kNumSwitches = 1;

class Switches {
 public:
  Switches() { }
  ~Switches() { }
  
  void Init();
  void Debounce();
  
  inline bool read(uint8_t index) const {
    return digitalRead(index);
  }
  
 private:
  uint8_t switch_state_[kNumSwitches];
  
  //DISALLOW_COPY_AND_ASSIGN(Switches);
};

}  // namespace lst

#endif  // LST_DRIVERS_SWITCHES_H_
