#ifndef _DFT_CALCULATOR_H_
#define _DFT_CALCULATOR_H_

#include "Array.h"
#include "types.h"

namespace fftw {

class DFTCalculator {
public:
	Array<Complex> calculateDFT(Array<Real> &reals);
	Array<Real> calculateInverseDFT(Array<Complex> &dft);
};

}

#endif
