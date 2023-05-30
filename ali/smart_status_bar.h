#pragma once
#include <thread>
#include "console.h"
class status_bar
{
public:
	status_bar(size_t completion, const char* barName, size_t precision = 0) {
		length = completion;
		this->precision = (float)completion / precision;
		this->barName = barName;
		myConsole.precision = 0;
		new std::thread(&status_bar::statusListener, this);
	}
	~status_bar() { finished = true; }

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

	void statusListener()
	{
		while (!finished && status / length * 100 != 100)
		{
			//precision = (float)length / (windowLength() / 10); // precision = (float)length / (windowLength() / 10);
			//console.logf('\r', precision, "    ", length, "    ", windowLength(), "               ");
			precision = windowLength() * length * 100;
			myConsole.logf('\r', barName, '[');
			int size = windowLength() / 10;
			for (size_t i = 0; i < status / length * size; i++)
			{
				myConsole.log('#');
			}
			for (size_t i = 0; i < windowLength() / 10 - (status / length * size); i++)
			{
				myConsole.log('-');
			}
			myConsole.logf("] - ", (float)status / length * 100, "%       ");
		}
		finished = true;
	}
	bool finished = false;
private:
	const char* barName = "";
	ali::Console myConsole;
	size_t length;
	size_t status = 0;
	float precision;
	int windowLength()
	{
		RECT rect;
		GetWindowRect(GetConsoleWindow(), &rect);
		POINT pnt{ rect.right - rect.left, rect.bottom - rect.top };
		return pnt.x;
	}
};