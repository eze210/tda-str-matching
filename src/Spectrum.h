#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_

#include "Signal.h"
#include "types.h"

class Spectrum: public Signal<fftw::Complex> {
private:
	explicit Spectrum(size_t size);

public:
	Spectrum(fftw::Array<fftw::Complex> &simple,
			 fftw::Array<fftw::Complex> &squared,
			 fftw::Array<fftw::Complex> &cube);

	Spectrum operator*(Spectrum &other);

	Signal<fftw::Real> getIDFT();
};

#endif
