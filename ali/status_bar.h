#pragma once
#include <thread>
#include "console.h"
class status_bar
{
public:
	status_bar(size_t completion, const char* barName, size_t precision = 10) {
		length = completion;
		this->precision = (float)completion / precision;
		this->barName = barName;
		myConsole.precision = 0;
		new std::thread(&status_bar::statusListener, this);
	}
	~status_bar() { terminate = true; }
	
	void increase(size_t amount = 1)
	{
		status += amount;
	}

	status_bar& operator++() { // Currently not working
		increase();
		return *this;
	}
	status_bar operator++(int)
	{
		return *this;
	}
	void operator+=(size_t amount)
	{
		increase(amount);
	}

	size_t status = 0;

	void statusListener()
	{
		while (!terminate)
		{
			myConsole.logf('\r', barName, '[');
			for (size_t i = 0; i < (float)status / precision; i++)
			{
				myConsole.log('#');
			}
			for (size_t i = 0; i < (int)length / precision - (status / precision) - 0.5; i++)
			{
				myConsole.log('-');
			}
			myConsole.logf("] - ", (float)status / length * 100, "% ");
		}
	}
private:
	const char* barName = "";
	ali::Console myConsole;
	size_t length;
	float precision;
	bool terminate = false;
};