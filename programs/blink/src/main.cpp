#include <Arduino.h>

// #include <drivers/system_clock.h>
#include <drivers/adc.h>
#include <ui.h>
#include <drivers/dac.h>
#include <drivers/shiftregister.h>
#include <app/app.h>

using namespace lst;

Adc adc;
Dac dac;
Ui ui;
ShiftRegister shiftregister;
//SystemClock systemClock;
App app_;

//PA15, PA12, PA11 

void setup() {
  //system_clock.Init();
  dac.Init();
  adc.Init();
  ui.Init(&adc, &app_);
  app_.Init(&ui, &adc, &dac);
  shiftregister.Init();
  shiftregister.Update(1);

  
}

void loop() {
  //set_trigger (digitalRead(PB1));
  //adc.Read();
  //shiftregister.Update(1);
  //shiftregister.Update(digitalRead(PB11) ? 128 : 0);

  app_.Process();
}