#ifndef _DFT_MATCHER_H_
#define _DFT_MATCHER_H_

#include "RealSignal.h"

#include <string>

class DFTMatcher {
private:
	RealSignal textAsSignal;
	RealSignal patternAsSignal;

	const std::wstring &text;
	const std::wstring &pattern;

public:
	DFTMatcher(const std::wstring &text, const std::wstring &pattern);
	void match();
};

#endif
