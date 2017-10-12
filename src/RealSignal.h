#ifndef _REAL_SIGNAL_H_
#define _REAL_SIGNAL_H_

#include "Signal.h"
#include "Spectrum.h"
#include "types.h"

class RealSignal: public Signal<fftw::Real> {
public:
	explicit RealSignal(size_t size);
	Spectrum getDFT();
};

#endif
