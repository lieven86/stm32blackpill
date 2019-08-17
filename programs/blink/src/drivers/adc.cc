#include <drivers/adc.h>

namespace lst {

void Adc::Init() {
    // multiplexer
    pinMode(PB5, OUTPUT);  // c
    pinMode(PA15, OUTPUT); // b
    pinMode(PA12, OUTPUT); // a

    current_adc_channel = ADC_MULTIPLEX_1; 
    current_multiplex_channel = 0;

    audio_divider_ = 0;

    for (int8_t i = 0; i < kNumChannels; i++) {
        values_[i] = 0;
    }
    
}

void Adc::Read() {
    switch (current_adc_channel) {
        case ADC_MULTIPLEX_1:
            digitalWrite(PA12, (current_multiplex_channel & 0x01));
            digitalWrite(PA15, ((current_multiplex_channel >> 1) & 0x01));
            digitalWrite(PB5, ((current_multiplex_channel >> 2) & 0x01));
            // store value
            values_[current_multiplex_channel] = analogRead(PA0);
            // advance multiplexer channel
            if (current_multiplex_channel == (1)) {
                if (audio_divider_ == 1) {
                    current_multiplex_channel++;
                    audio_divider_ = 0;
                } else {
                    audio_divider_++;
                }
            } else {
                current_multiplex_channel++;
            }
            
            if (current_multiplex_channel == kNumChannels - 2) {
                current_multiplex_channel = 0;
                current_adc_channel = ADC_POT_1;
            }
            break;
        case ADC_POT_1:
            values_[8] = analogRead(PA2);
            current_adc_channel = ADC_POT_2;
            break;
        case ADC_POT_2:
            values_[9] = analogRead(PA1);
            current_adc_channel = ADC_MULTIPLEX_1;
            break;
        default:
            break;
    }
}
}  // namespace lst
