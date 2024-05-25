#pragma once
#include <vector>
using ull = unsigned long long;
#define MAX_UNSIGNED (ull)-1

class infinint
{
public:
	infinint() {

	}
	~infinint(){}

	void operator+=(ull adder) {
		ull saved = data[data.size()-1];
		if (data[data.size() - 1] + adder > saved) data[data.size() - 1] += adder;
		else {
			data[data.size() - 1] = MAX_UNSIGNED;
			data.push_back(adder - (MAX_UNSIGNED - saved));
		}
	}

	std::vector<ull> get() {
		return data;
	}
private:
	std::vector<ull> data{0};
};