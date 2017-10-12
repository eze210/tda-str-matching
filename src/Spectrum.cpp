#include "DFTCalculator.h"
#include "Spectrum.h"

Spectrum::Spectrum(size_t size) : Signal<fftw::Complex>(size) {
}

Spectrum::Spectrum(fftw::Array<fftw::Complex> &simple,
		 fftw::Array<fftw::Complex> &squared,
		 fftw::Array<fftw::Complex> &cube) :
	Signal<fftw::Complex>(simple, squared, cube) {
}

Spectrum Spectrum::operator*(Spectrum &other) {
	Spectrum product(this->length);

	// (a + jb) * (c + jd) = (ac - bd) + j * (ad + bc)
	for (size_t i = 0; i < this->length * 2; ++i) {
		product.cube[i][0] = other.cube[i][0] * this->simple[i][0] -
							   other.cube[i][1] * this->simple[i][1];
		product.cube[i][1] = other.cube[i][0] * this->simple[i][1] +
							   other.cube[i][1] * this->simple[i][0];

		product.squared[i][0] = other.squared[i][0] * this->squared[i][0] -
								other.squared[i][1] * this->squared[i][1];
		product.squared[i][1] = other.squared[i][0] * this->squared[i][1] +
								other.squared[i][1] * this->squared[i][0];

		product.simple[i][0] = other.simple[i][0] * this->cube[i][0] -
							 other.simple[i][1] * this->cube[i][1];
		product.simple[i][1] = other.simple[i][0] * this->cube[i][1] +
							 other.simple[i][1] * this->cube[i][0];
	}

	return product;
}

Signal<fftw::Real> Spectrum::getIDFT() {
	fftw::DFTCalculator calculator;
	fftw::Array<fftw::Real> simpleIDFT = 
		calculator.calculateInverseDFT(this->simple);
	fftw::Array<fftw::Real> squaredIDFT = 
		calculator.calculateInverseDFT(this->squared);
	fftw::Array<fftw::Real> cubeIDFT =
		calculator.calculateInverseDFT(this->cube);
	Signal<fftw::Real> idft(simpleIDFT, squaredIDFT, cubeIDFT);
	return idft;
}
