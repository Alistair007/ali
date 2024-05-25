#pragma once
template<typename T>
class vector
{
public:
	vector();
	~vector();

	void push_back(T value) {
		if (size != capacity) {
			data[size + 1] = value;
		}
		size++;
	}
private:
	T* data;
	size_t capacity = 4;
	size_t size = 0;
};