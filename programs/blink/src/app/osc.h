#include <lib.h>
#include <math.h>
#include "resources.h"

#ifndef LST_OSC_H
#define LST_OSC_H

using namespace lib;

namespace lst {

enum OscillatorMode {
	OSCILLATOR_MODE_SINE = 0,
	OSCILLATOR_MODE_TRIANGLE = 1,
    OSCILLATOR_MODE_SAWU,
    OSCILLATOR_MODE_SQUARE,
	OSCILLATOR_MODE_USER,
    kNumOscillatorModes
};


class Osc
{
public:
	Osc() { }
	~Osc() { }
    
    void init();

	void setWaveform(int mode);

	inline uint8_t getPhase() {
		return phase_;
	}

	inline int16_t getFm() {
		return fm >> fmDepth;
	}

	inline void setPm(int16_t f) {
		pm = static_cast<uint32_t>(f >> 2);
	}

	inline void setPulseWidth(uint8_t pw) {
		pulseWidth_ = pw;
	}

	inline void setFm(int16_t f) {
		fm = static_cast<uint16_t>(f >> 2);
	}

	inline void setFmDepth(int16_t f) {
		fmDepth = mOscillatorMode <= 7 ? f + 7 : f + 11;
	}

	inline void setFmDepth() {
		fmDepth = mOscillatorMode <= 7 ? 7 : 13;
	}

	inline void setAm(float f) {
		am = f;
	}

	inline void setPitch(int16_t pitch) {
        if (abs(pitch - last_pitch_) > 16) {
	        pitch_ = pitch;
            last_pitch_ = pitch_;
        }
	}

	inline void setUserTable(uint8_t position, int16_t value) {
		userbuffer[position] = value;
	}

	inline void recordTable(uint8_t value) {
		userbuffer[recordHead] = value;
		recordHead = (recordHead + 1) % 256;
	}

	int16_t Render(uint8_t sync);

private:
	uint32_t ComputePhaseIncrement(int16_t midi_pitch);

	OscillatorMode mOscillatorMode;

	uint32_t pm;
	uint16_t fm;
	int16_t fmDepth;
	uint32_t am;
	uint8_t pulseWidth_;

	uint32_t phase_;
	uint32_t phase_increment_;
	uint32_t previous_phase_increment_;
	int16_t pitch_;
    int16_t last_pitch_;

	uint32_t tableSize;
	uint8_t userbuffer[257];
	uint8_t recordHead;
	DISALLOW_COPY_AND_ASSIGN(Osc);

};
}

#endif // OSC_3_H