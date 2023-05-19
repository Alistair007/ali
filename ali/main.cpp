#include "console.h"
#include "timer.h"

int main()
{
	ali::Timer timer;
	const int times = 1000000000;
	
	for (size_t i = 0; i < times; i++)
	{
		ali::console.enqueue(i);
	}

	timer.stop();
	auto x = timer.get_time<std::chrono::milliseconds>().count();
	std::cout << '\n' << x << "ms. " << (float)x / times << " milliseconds/log.";
}