#ifndef _DFT_MATCHER_H_
#define _DFT_MATCHER_H_

#include "RealSignal.h"

class DFTMatcher {
private:
	RealSignal textAsSignal;
	RealSignal patternAsSignal;

	const String &text;
	const String &pattern;

public:
	DFTMatcher(const String &text, const String &pattern);
	void match();
};

#endif
