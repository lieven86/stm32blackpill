#include <drivers/digital_out.h>

namespace lst {

void DigitalOut::Init() {
    pinMode(PB0, OUTPUT); // 6
    pinMode(PB6, OUTPUT); // 4
    pinMode(PB7, OUTPUT); // 2
    pinMode(PA6, OUTPUT); // 1
    pinMode(PA7, OUTPUT); // 8
    pinMode(PA8, OUTPUT); // 3
    pinMode(PA9, OUTPUT); // 5
    pinMode(PA10, OUTPUT); // 7

    // todo put pins in array and function write by number
}

void DigitalOut::Write(uint8_t channel, uint8_t value) {
    digitalWrite(channel, value);
}

}  // namespace lst
