#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include "Array.h"
#include "types.h"

template<class T> class Callable {
public:
	virtual void operator()(size_t index, 
		T &simple, T &squared, T &cube, 
		size_t n) = 0;
};

template<class T> class Signal {
protected:
	size_t length;
	fftw::Array<T> simple;
	fftw::Array<T> squared;
	fftw::Array<T> cube;

public:
	Signal(fftw::Array<T> &simple,
		   fftw::Array<T> &squared,
		   fftw::Array<T> &cube) :
		length(simple.size()/2),
		simple(std::move(simple)),
		squared(std::move(squared)),
		cube(std::move(cube)) {}

	explicit Signal(size_t length) :
			length(length),
			simple(2 * length),
			squared(2 * length),
			cube(2 * length) {
	}

	Signal(size_t length, T initValue) :
			length(length),
			simple(2 * length, initValue),
			squared(2 * length, initValue),
			cube(2 * length, initValue) {
	}

	void parseWString(const String &wstring) {
		size_t length = wstring.length();
		for (size_t i = 0; i < length; ++i) {
			simple[i] = (T) wstring[i];
			squared[i] = simple[i] * simple[i];
			cube[i] = simple[i] * squared[i];
		}
	}

	void parseWStringReverse(const String &wstring) {
		size_t length = wstring.length();
		for(size_t i=0; i < length; i++){
			simple[i] = (T) wstring[length - i - 1];
			squared[i] = simple[i] * simple[i];
			cube[i] = simple[i] * squared[i];
		}
	}

	void iterate(Callable<T> &callable, size_t from, size_t until) {
		for (size_t i = from; i <= until; ++i) {
			callable(i - from, simple[i], squared[i], cube[i], until);
		}
	}
};

#endif
