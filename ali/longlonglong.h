#pragma once
#include <iostream>

#define MAX_SIZE 9223372036854775807
#define FULL 9223372036854775807

class longlonglong // Basically a vector of ints
{
public:
	longlonglong(long long value) {
		data = new long long[1];
		data[0] = value;
	}
	~longlonglong() {
		printf("terminated!");
		//delete[] data; // F**k memory leaks
	}
	void add(long long value)
	{
		if (data[datasize] + value > MAX_SIZE)
		{
			long long* temp = data;
			data = new long long[datasize + 1];
			for (size_t i = 0; i < datasize; i++)
			{
				temp[i] = data[i];
			}
			temp[datasize] = FULL;
			temp[datasize + 1] = MAX_SIZE - data[datasize];
			datasize++;
			data = temp;
			delete[] temp;
		}
		else data += value;
	}
	long long* data;

private:
	size_t datasize = 0;
};