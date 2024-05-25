#pragma once
#include <initializer_list>

const int tab64[64] = {
	63,  0, 58,  1, 59, 47, 53,  2,
	60, 39, 48, 27, 54, 33, 42,  3,
	61, 51, 37, 40, 49, 18, 28, 20,
	55, 30, 34, 11, 43, 14, 22,  4,
	62, 57, 46, 52, 38, 26, 32, 41,
	50, 36, 17, 19, 29, 10, 13, 21,
	56, 45, 25, 31, 35, 16,  9, 12,
	44, 24, 15,  8, 23,  7,  6,  5 };

int log2_64_f(uint64_t value)
{
	if (value == 0 || value == 1) return 0;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	value |= value >> 32;
	return tab64[((uint64_t)((value - (value >> 1)) * 0x07EDD5E59A4E28C2)) >> 58];
}

template<typename T>
class tv
{
public:
	tv() {
		s_capacity = 2;
		ptrs[0] = new T[2];
		s_currentPtrSize = 0;
		s_size = 0;
		s_currentPtr = 0;
	}
	tv(std::initializer_list<T> elems) {

	}
	tv(size_t size);
	~tv() {
		for (size_t i = 0; i < s_currentPtr; i++)
		{

			delete[] ptrs[i]; // ???
		}
	}

	void push_back(const T& data) {
		if (s_currentPtrSize < s_capacity) {
			ptrs[s_currentPtr][s_currentPtrSize] = data;
		}
		else {
			ptrs[s_currentPtr + 1] = new T[s_capacity * 2];
			s_currentPtrSize = 0;
			s_currentPtr++;
			s_capacity *= 2;
			ptrs[s_currentPtr][0] = data;
		}
		s_currentPtrSize++;
		s_size++;
	}

	T& operator[](size_t index) {
		if (index >= s_size) {
			throw std::out_of_range("Index out of range");
		}

		return ptrs[log2_64_f(index + 2) - 1][index - (1ULL << (log2_64_f(index + 2))) + 2];
	}

	T* ptrs[32];
	size_t s_currentPtr;
	size_t s_currentPtrSize;
	size_t s_capacity;
	size_t s_size;
private:
	

	void f_getCurrentPtrCapacity() {

	}
};