#include <drivers/dac.h>

namespace lst {

void Dac::Init() {
    pinMode(DAC_CS, OUTPUT);
    digitalWrite(DAC_CS, HIGH);
    pinMode(DAC_CS2, OUTPUT);
    digitalWrite(DAC_CS2, HIGH);
    MY_SPI.setSCLK(DAC_SCK);
    MY_SPI.setMOSI(DAC_MOSI);
    MY_SPI.begin();
}

void Dac::Update(char channel, int val) {
    byte lVal = val;
    byte hVal = (val >> 8);
    if (channel == 0) { // 0 = bipolar
        digitalWrite(DAC_CS2, LOW);
    } else if (channel == 1) {
        digitalWrite(DAC_CS, LOW);
    } else {
        return;
    }

    MY_SPI.transfer(hVal | DAC_FLAGS_A);
    MY_SPI.transfer(lVal);

    if (channel == 0) {
        digitalWrite(DAC_CS2, HIGH);
    } else if (channel == 1) {
        digitalWrite(DAC_CS, HIGH);
    }
}

}  // namespace lst
