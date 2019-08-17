#include <drivers/switches.h>

namespace lst {
  
using namespace std;

void Switches::Init() {
    pinMode(PB1, INPUT);
    
    for (int8_t i = 0; i < kNumSwitches; ++i) {
      switch_state_[i] = 0xff;
    }
}

void Switches::Debounce() {
  switch_state_[kNumSwitches - 1] = (switch_state_[kNumSwitches - 1] << 1) | \
      (digitalRead(PB1) & (0x01<<0));
}

}  // namespace lst
