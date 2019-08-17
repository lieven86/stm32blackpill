#ifndef LST_APP_H
#define LST_APP_H

#include <Arduino.h>
#include <lib.h>
#include <resources.h>
#include <drivers/adc.h>
#include <drivers/dac.h>
#include <ui.h>
#include <drivers/digital_out.h>
#include <app/noise.h>
#include <app/osc.h>

namespace lst {

enum PlaybackMode {
  TEST_MODE,
  MODE_LAST
};

const uint8_t kNumtriggers = 1;

class App {
    public:
        App() { }
        ~App() { }

        void Init(Ui *ui, Adc *adc, Dac *dac);
        void Process();
        void set_trigger(bool trigger);
        
    private:
        Ui *ui_;
        Adc *adc_;
        Dac *dac_;
        DigitalOut digital_out;
        Noise noise;
        Osc osc_;
        Osc osc_2;

        uint8_t current_dac;

        uint8_t sync_;
        uint8_t previous_cv;
        uint8_t cv_count;
        uint8_t sub_divide;

        bool trigger_, previous_trigger_;
        bool reset_trigger_armed_[kNumtriggers];
        bool reset_triggered_[kNumtriggers];
        uint8_t previous_reset_[kNumtriggers];

        void handleTrigger(int8_t nr, uint8_t reset);

        DISALLOW_COPY_AND_ASSIGN(App);
};
}

#endif // LST_APP_H
