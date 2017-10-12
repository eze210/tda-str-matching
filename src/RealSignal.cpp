#include "DFTCalculator.h"
#include "RealSignal.h"


RealSignal::RealSignal(size_t size) : Signal<fftw::Real>(size, 0.0) {
}

Spectrum RealSignal::getDFT() {
	fftw::DFTCalculator calculator;
	fftw::Array<fftw::Complex> simpleDFT = 
		calculator.calculateDFT(this->simple);
	fftw::Array<fftw::Complex> squaredDFT = 
		calculator.calculateDFT(this->squared);
	fftw::Array<fftw::Complex> cubeDFT =
		calculator.calculateDFT(this->cube);
	Spectrum spectrum(simpleDFT, squaredDFT, cubeDFT);
	return spectrum;
}
