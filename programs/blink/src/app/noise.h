#ifndef LST_NOISE_H_
#define LST_NOISE_H_

#include <lib.h>

namespace lst {

class Noise {
 public:
  Noise() { }
  ~Noise() { }

  void Init() {
    x = 0; 
    y = 0;
    z = 0;
    a = 1;
  }
  
  inline uint8_t xorshf8(void) { //period 2^96-1
    uint8_t t = x ^ (x >> 1);
    x=y;
    y=z;
    z=a;
    a = z ^ t ^ ( z >> 3) ^ (t << 1);

    return a;
  }

  inline uint8_t zero_one(void) {
      return xorshf8() > 100 ? 0x1 : 0x0;
  }

 private:
    uint8_t x, y, z, a;
    DISALLOW_COPY_AND_ASSIGN(Noise);
};

}  // namespace lst

#endif  // LST_NOISE_H_
