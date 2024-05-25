#pragma once
#include <iostream>
#include "console.h"

template<typename T>
class observer {
public:
	observer(T val, const char* name) {
		this->name = name;
		myConsole.logf(name, " = ", val, '\n');
	}
	T& g() {
		std::cin.ignore();
		myConsole.logf(name, " = ", val, '\n');
		return val;
	}
	~observer() {
		std::cin.ignore();
		myConsole.logf(name, " = ", val, '\n');
	}
private:
	T val;
	const char* name;
	ali::Console myConsole;
};