#include "DFTMatcher.h"

#include <iostream>
#include <string>

#include <sstream>
#include <fstream>
#include <iostream>

const std::wstring readFile(const char* filename) {
    std::wifstream wif(filename,std::ios::binary);
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

int main(int argc, const char *argv[]) {
	std::cout << "Searching '" << argv[2] << 
		"'' in '" << argv[1] << "'" << std::endl;

	clock_t begin = clock();
	const std::wstring text = readFile(argv[1]);

	wchar_t patternBuffer[100];
  	swprintf(patternBuffer, 100, L"%s", argv[2]);
	const std::wstring pattern(patternBuffer);

	DFTMatcher matcher(text, pattern);

	clock_t fileWasLoaded = clock();
	std::cout << "Time to load the file: " << 
		(double(fileWasLoaded - begin) / CLOCKS_PER_SEC) << std::endl;
	
	matcher.match();

	return 0;
}
