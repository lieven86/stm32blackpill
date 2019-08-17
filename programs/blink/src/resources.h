#ifndef LST_RESOURCES_H_
#define LST_RESOURCES_H_

#include <lib.h>

namespace lst {

extern const uint16_t sine[];
#define SINE 0
#define SINE_SIZE 120

extern const uint8_t sinebuffer[];
extern const uint8_t trianglebuffer[];
extern const uint8_t sawubuffer[];
extern const uint8_t squarebuffer[];

extern const uint32_t osc_inc[];

#define SINEBUFFER 0
#define SINEBUFFER_SIZE 257
#define TRIANGLEBUFFER 0
#define TRIANGLEBUFFER_SIZE 257
#define SAWUBUFFER 0
#define SAWUBUFFER_SIZE 257
#define SQUAREBUFFER 0
#define SQUAREBUFFER_SIZE 257

}

#endif
