#include "DFTMatcher.h"

#include <iostream>
#include <fstream>
#include <sstream>

const String readFile(const char* filename) {
    ifstream wif(filename, std::ios::binary);
    sstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

int main(int argc, const char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: ./tp <filename> <pattern>" << std::endl;
		return 1;
	}

	std::cout << "Searching '" << argv[2] << 
		"' in '" << argv[1] << "'" << std::endl;

	clock_t begin = clock();
	const String text = readFile(argv[1]);

#ifdef USE_WSTRING
	Character patternBuffer[100];
  	SPrint(patternBuffer, 100, StrFmt, argv[2]);
	const String pattern(patternBuffer);
#else
	const String pattern(argv[2]);
#endif

	DFTMatcher matcher(text, pattern);

	clock_t fileWasLoaded = clock();
	std::cout << "Time to load the file: " << 
		(double(fileWasLoaded - begin) / CLOCKS_PER_SEC) << std::endl;
	
	matcher.match();

	return 0;
}
