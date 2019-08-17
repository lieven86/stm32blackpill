#ifndef LST_SHIFTREGISTER_H_
#define LST_SHIFTREGISTER_H_

#include <Arduino.h>
#include <lib.h>

namespace lst {

class ShiftRegister {
 public:
  ShiftRegister() { }
  ~ShiftRegister() { }
  
  void Init() {
    latchPin = PB10;
    clockPin = PB9;
    dataPin  = PB8;
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
  }

  inline void Update(uint8_t v) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, v);
    digitalWrite(latchPin, HIGH);
  }

  private:
    uint8_t latchPin;
    uint8_t clockPin;
    uint8_t dataPin;
    DISALLOW_COPY_AND_ASSIGN(ShiftRegister);
};

}  // namespace lst

#endif  // LST_SHIFTREGISTER_H_
