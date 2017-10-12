#include "DFTMatcher.h"
#include "DFTCalculator.h"
#include "Spectrum.h"

#include <cmath>
#include <iostream>
#include <string>

static const double comparisonThreshold =  0.00001;

class MatchCheck : public Callable<fftw::Real> {
private:
	const std::wstring &text;
	const std::wstring &pattern;
	size_t matches;
	size_t falsePossitives;

public:
	MatchCheck(const std::wstring &text, const std::wstring &pattern) : 
		text(text), pattern(pattern), matches(0), falsePossitives(0) {}
	void operator()(size_t index, 
					fftw::Real &simple, 
					fftw::Real &squared, 
					fftw::Real &cube,
					size_t n) {
		double result = (cube/(n*2)) - (squared/n) + (simple/(n*2));
		if (fabs(result) <= comparisonThreshold) {
			if (text.compare(index, pattern.length(), pattern) == 0) {
				++matches;
				std::cout << "Match at index: " << index << 
							 " with result: " << result << std::endl;
			} else {
				++falsePossitives;
				std::cout << "False possitive at index: " << index << 
							 " with result: " << result << std::endl;
			}
		}
	}

	void printStatistics() {
		std::cout << "Matches: " << matches << 
			"\nFalse possitives: " << falsePossitives << std::endl;
	}
};

DFTMatcher::DFTMatcher(
		const std::wstring &text, 
		const std::wstring &pattern) :
			textAsSignal(text.length()), 
			patternAsSignal(text.length()),
			text(text), pattern(pattern) {
	textAsSignal.parseWString(text);
	patternAsSignal.parseWStringReverse(pattern);
}

void DFTMatcher::match() {
	clock_t begin = clock();
	Spectrum textSpectrum = textAsSignal.getDFT();
	Spectrum patternSpectrum = patternAsSignal.getDFT();
	clock_t dftsTime = clock();

	Spectrum product = textSpectrum * patternSpectrum;
	clock_t productTime = clock();

	Signal<fftw::Real> idft = product.getIDFT();
	clock_t idftTime = clock();

	MatchCheck checker(text, pattern);
	idft.iterate(checker, pattern.length() - 1, text.length() - 1);
	clock_t collectResultsTime = clock();

	std::cout << "Times:" <<
		"\n\tDFTs calculation: " << 
			(double(dftsTime - begin) / CLOCKS_PER_SEC) <<
		"\n\tProduct calculation: " << 
			(double(productTime - dftsTime) / CLOCKS_PER_SEC) <<
		"\n\tIDFT calculation: " << 
			(double(idftTime - dftsTime) / CLOCKS_PER_SEC) <<
		"\n\tTime to check results: " << 
			(double(collectResultsTime - idftTime) / CLOCKS_PER_SEC) <<
		"\n\tTOTAL: " << 
			(double(collectResultsTime - begin) / CLOCKS_PER_SEC) <<
		std::endl;
	checker.printStatistics();
}


