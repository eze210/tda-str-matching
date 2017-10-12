#ifndef _FFTW_ARRAY_H_
#define _FFTW_ARRAY_H_

#include <fftw3.h>
#include <stdlib.h>

namespace fftw {

template<class T> class Array {
private:
	T *array;
	size_t _size;
	Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

public:
	explicit Array(size_t size) :
		array(static_cast<T*>(fftw_malloc(sizeof(T) * size))),
		_size(size) {
	}

	Array(size_t size, T initValue) :
		array(static_cast<T*>(fftw_malloc(sizeof(T) * size))),
		_size(size) {
		for (size_t i = 0; i < _size; ++i)
			array[i] = initValue;
	}

    Array(Array&& other) : array(other.array), _size(other._size) {
		other.array = NULL;
		other._size = 0;
    }

    Array& operator=(Array&& other) {
    	this->array = other.array;
    	this->_size = other._size;
    	other.array = NULL;
    	other._size = 0;
    	return *this;
    }

	T& operator[](size_t position) {
		if (position >= _size)
			throw "Index out of bounds";
		return array[position];
	}

	T *data() {
		return array;
	}

	size_t size() const {
		return _size;
	}

	~Array() {
		if (array != NULL)
			fftw_free(array);
	}
};

}

#endif
