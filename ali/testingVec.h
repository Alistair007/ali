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
class tv // Iterators are not possible since it's not a continuous array, right?
{
public:
	tv() {
		s_currentPtrCapacity = 2;
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
		ensure_capacity(s_size + 1);
		ptrs[s_currentPtr][s_currentPtrSize++] = data;
		s_size++;
		if (s_currentPtrSize == s_capacity) {
			s_currentPtrSize = 0;
			s_capacity *= 2;
			s_currentPtr++;
			ptrs[s_currentPtr] = new T[s_capacity];
		}
	}

	T& operator[](size_t index) {
		if (index >= s_size) {
			throw std::out_of_range("Index out of range");
		}

		return ptrs[f_getBaseByIndex(index)][f_getIndexByIndex(index)];
	}

	T operator[] (size_t index) const {
		if (index >= s_size) {
			throw std::out_of_range("Index out of range");
		}

		return ptrs[f_getBaseByIndex(index)][f_getIndexByIndex(index)];
	}

	size_t size() const {
		return s_size;
	}

	size_t capacity() const {
		return s_capacity;
	}

	/*template<typename Lambda>
	void for_each(Lambda&& lambda) {
		for (size_t i = 0; i < s_size; ++i) {
			lambda(ptrs[f_getBaseByIndex(i)][f_getIndexByIndex(i)]);
		}
	}*/

	void insert(size_t index, const T& data) {
		if (index > s_size) {
			throw std::out_of_range("Index out of range");
		}

		this->push_back(ptrs[s_currentPtr][s_currentPtrSize - 1]);

		for (size_t i = index + 1; i < s_size; i++)
		{
			(*this)[s_size - i] = (*this)[s_size - i - 1];
		}

		(*this)[index] = data;
	}

	void pop_back() {
		if (s_currentPtrSize == 0) {
			delete[] ptrs[s_currentPtr];
			s_currentPtr--;
			s_capacity /= 2;
			s_currentPtrCapacity /= 2;
			s_currentPtrSize = s_currentPtrCapacity;
		}
		else if (s_currentPtrCapacity == s_currentPtrSize) {

		}
		s_currentPtrSize--;
		s_size--;
	}


	void operator+=(const T& data) {
		ensure_capacity(s_size + 1);
		ptrs[s_currentPtr][s_currentPtrSize++] = data;
		s_size++;
		if (s_currentPtrSize == s_capacity) {
			s_currentPtrSize = 0;
			s_capacity *= 2;
			s_currentPtr++;
			ptrs[s_currentPtr] = new T[s_capacity];
		}
	}

	tv<T>& operator--()
	{
		this->pop_back();
		return *this; // return new value by reference
	}

	// postfix decrement
	tv<T> operator--(int)
	{
		tv<T> old = *this; // copy old value
		operator--();  // prefix decrement
		return old;    // return old value
	}
private:
	T* ptrs[32];
	size_t s_currentPtr, s_currentPtrSize, s_capacity, s_size, s_currentPtrCapacity;

	inline unsigned short f_getBaseByIndex(size_t index) const {
		return log2_64_f(index + 2) - 1;
	}

	inline unsigned short f_getIndexByIndex(size_t index) const {
		return index - (1ULL << (log2_64_f(index + 2))) + 2;
	}
	void ensure_capacity(size_t new_size) {
		if (new_size < s_capacity) {
			size_t new_capacity = s_capacity;
			while (new_capacity < new_size) {
				new_capacity *= 2;
				s_currentPtrCapacity *= 2;
				s_currentPtr++;
				//console.logf(s_currentPtr, '\n');
				ptrs[s_currentPtr] = new T[new_capacity];
			}
			s_capacity = new_capacity;
		}
	}
};