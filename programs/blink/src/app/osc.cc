#include <app/osc.h>
#include <resources.h>

namespace lst {

using namespace std;
using namespace lib;

static const size_t kNumZones = 15;
static const int16_t kHighestNote = 128 * 128;
static const int16_t kPitchTableStart = 128 * 116;
static const int16_t kOctave = 12 * 128;

void Osc::init() {
	setWaveform(0);

	tableSize = mOscillatorMode <= 7 ? 16 : 256;

	pm = 0;
	am = 0;
	fm = 0;
	fmDepth = 13;

	phase_ = 0;
	phase_increment_ = 0;
	previous_phase_increment_ = 0;
	pitch_ = 60 << 7;

	recordHead = 0;
  userbuffer[0] = 0;
  userbuffer[256] = 0;
  userbuffer[255] = 0;

}

void Osc::setWaveform(int mode) {
	mOscillatorMode = (OscillatorMode)mode;
}

uint32_t Osc::ComputePhaseIncrement(int16_t midi_pitch) {
  if (midi_pitch >= kHighestNote) {
    midi_pitch = kHighestNote - 1;
  }
  
  int32_t ref_pitch = midi_pitch;
  ref_pitch -= kPitchTableStart;
  
  size_t num_shifts = 0;
  while (ref_pitch < 0) {
    ref_pitch += kOctave;
    ++num_shifts;
  }
  
  uint32_t a = osc_inc[ref_pitch >> 4];
  uint32_t b = osc_inc[(ref_pitch >> 4) + 1];
  uint32_t phase_increment = a + \
      (static_cast<int32_t>(b - a) * (ref_pitch & 0xf) >> 4);
  phase_increment >>= num_shifts;
  return phase_increment;
}

int16_t Osc::Render(uint8_t sync) {
	phase_increment_ = ComputePhaseIncrement(pitch_ + fm);

	if (pitch_ >= kHighestNote) {
    pitch_ = kHighestNote;
  } else if (pitch_ < 0) {
    pitch_ = 0;
  }

  phase_ += phase_increment_;
    
  if (sync) {
  	phase_ = 0;
  }
    //uint32_t phaseModulation = (uint32_t)tableSize * (uint32_t)pm;
    //return sine1024_1[(phase_ >> 22 % tableSize) + phaseModulation];

    //phase_ = (phase_ + tableSize * pm);
    //return sinebuffer[phase_ % 16];

  switch (mOscillatorMode) {
    case OSCILLATOR_MODE_SINE: 
      return Interpolate824(sinebuffer, phase_);
    case OSCILLATOR_MODE_TRIANGLE:
      return Interpolate824(trianglebuffer, phase_);
    case OSCILLATOR_MODE_SAWU:
      return Interpolate824(sawubuffer, phase_);
    case OSCILLATOR_MODE_SQUARE:
      return Interpolate824(squarebuffer, phase_);
    case OSCILLATOR_MODE_USER:
      return Interpolate824(userbuffer, phase_);
    case kNumOscillatorModes:
      return 0;
  }
	return 0;
}

}
