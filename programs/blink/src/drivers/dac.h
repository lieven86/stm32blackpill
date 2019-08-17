#ifndef LST_DAC_H_
#define LST_DAC_H_

#include <Arduino.h>
#include <SPI.h>
#include <lib.h>

// dac
#define DAC_CS    PB12
#define DAC_SCK   PB13
#define DAC_MOSI  PB15
#define DAC_CS2   PB14

#define DAC_FLAGS_A 0b00110000 //Select DAC channel A (MCP 4921 or (MCP 4922)
#define DAC_FLAGS_B 0b10110000 //Select DAC channel B (only on MCP 4922)

namespace lst {

class Dac {
 public:
  Dac() { }
  ~Dac() { }
  
  void Init();
  void Update(char channel, int val);
  
  private:
    SPIClass MY_SPI;
    DISALLOW_COPY_AND_ASSIGN(Dac);
};

}  // namespace lst

#endif  // LST_SHIFTREGISTER_H_
