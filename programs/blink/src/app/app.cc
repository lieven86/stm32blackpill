#include <app/app.h>

namespace lst {

void App::Init(Ui *ui, Adc *adc, Dac *dac) {
    ui_ = ui;
    adc_ = adc; 
    dac_ = dac;
    digital_out.Init();
    noise.Init();
    osc_.init();
    osc_2.init();
    osc_2.setWaveform(1);
    current_dac = 0;
}

void App::set_trigger(bool trigger) {
    previous_trigger_ = trigger_;
    trigger_ = trigger;
    sync_ = 0;
    if (trigger_ && !previous_trigger_) {
        previous_trigger_ = trigger_;
        sync_ = 1; 
    }
}

void App::Process() {
    //bool n = noise.zero_one();
    //digital_out.Write(PB0, n);
    //digital_out.Write(PB6, n);
    //digital_out.Write(PB7, n);
    //digital_out.Write(PA6, n);
    //digital_out.Write(PA7, n);
    //digital_out.Write(PA8, n);
    //digital_out.Write(PA9, n);
    //digital_out.Write(PA10, n);

    //int16_t pitch = adc_->value(8) << 4;
    int16_t pitch = 8000;
    osc_.setPitch(pitch);
    //osc_.setWaveform(1);
    osc_2.setPitch(pitch);
    //osc_2.setWaveform(1);
    //osc_.setFm(adc_->value(0) << 4);
    //osc_2.setFm(adc_->value(1) << 4);

    int16_t out2 = ((osc_2.Render(0) >> 4) + 2048);
    dac_->Update(0, out2);
    int16_t out = ((osc_.Render(0) >> 4) + 2048);
    dac_->Update(1, out);

    // switch (current_dac) {
    //     case 0: {
    //         int16_t out2 = ((osc_2.Render(0) >> 4) + 2048);
    //         dac_->Update(0, out2);
    //         current_dac = 1;
    //     }   break;
    //     case 1: {
    //         int16_t out = ((osc_.Render(0) >> 4) + 2048);
    //         dac_->Update(1, out);
    //         current_dac = 0;
    //     }    break;
    //     default:
    //         break;
    // }
}

}  // namespace lst
