#include "console.h"
#include "timer.h"
#include "smart_status_bar.h"
#include <windows.h>

int main()
{
	// Speed comparison
	constexpr size_t times = 100000;
	ali::Timer cout;
	for (size_t i = 0; i < times; i++)
	{
		ali::qout << i;
	}
	ali::qout--;
	cout.stop();
	ali::Timer consoleLog;
	for (size_t i = 0; i < times; i++)
	{
		console.log(i);
	}
	consoleLog.stop();
	ali::cout << "\n" << cout.get_time<ali::milliseconds>().count() << " cout, " << consoleLog.get_time<ali::milliseconds>().count() << " console.log() ";
}

//void printShowcase()
//{
//const size_t times = 10000;
//ali::Timer x;
//for (size_t i = 0; i < times; i++)
//{
//std::cout << i;
//}
//auto cout = x.time_passed<ali::milliseconds>().count();
//for (size_t i = 0; i < times; i++)
//{
//printf("%ld", i);
//}
//auto ptf = x.time_passed<ali::milliseconds>().count() - cout;
//for (size_t i = 0; i < times; i++)
//{
//ali::console.log(i);
//}
//auto consolelog = x.time_passed<ali::milliseconds>().count() - cout - ptf;
//for (size_t i = 0; i < times; i++)
//{
//ali::console.enqueue(i);
//}
//ali::console.dequeue();
//auto queue = x.time_passed<ali::milliseconds>().count() - cout - ptf - consolelog;
//std::cout << "\nstd::cout: " << cout << "\nprintf(): " << ptf << "\nconsole.log(): " << consolelog << "\nqueue: " << queue;
//}