#ifndef _FFTW_TYPES_H_
#define _FFTW_TYPES_H_

#include <fftw3.h>
#include <string>

namespace fftw {
	typedef double Real;
	typedef fftw_complex Complex;
}

#ifdef USE_WSTRING
typedef std::wstring String;
#define ifstream std::wifstream
#define sstream std::wstringstream
#define output std::wcout
#define Character wchar_t
#define SPrint swprintf
#define StrFmt L"%s"
#else
typedef std::string String;
#define ifstream std::ifstream
#define sstream std::stringstream
#define output std::cout
#define Character char
#define SPrint snprintf
#define StrFmt "%s"
#endif

#endif
