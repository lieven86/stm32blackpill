#ifndef LST_DIGITAL_OUT_H_
#define LST_DIGITAL_OUT_H_

#include <Arduino.h>
#include <lib.h>

namespace lst {

class DigitalOut {
 public:
  DigitalOut() { }
  ~DigitalOut() { }
  
  void Init();
  void Write(uint8_t channel, uint8_t value);
  
 private:
  DISALLOW_COPY_AND_ASSIGN(DigitalOut);
};

}  // namespace lst

#endif  // LST_SYSTEM_CLOCK_H_
