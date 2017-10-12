#include "DFTCalculator.h"
#include "types.h"

#include <fftw3.h>
#include <utility>

namespace fftw {

Array<Complex> DFTCalculator::calculateDFT(Array<Real> &reals) {
	Array<Complex> dft(reals.size());
	fftw_plan plan;
	plan = fftw_plan_dft_r2c_1d(
		reals.size(), 
		reals.data(), 
		dft.data(),
		FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	return std::move(dft);
}

Array<Real> DFTCalculator::calculateInverseDFT(Array<Complex> &dft) {
	Array<Real> idft(dft.size());
	fftw_plan plan;
	plan = fftw_plan_dft_c2r_1d(
		dft.size(),
		dft.data(),
		idft.data(),
		FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	return std::move(idft);
}

}
