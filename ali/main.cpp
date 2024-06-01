#include "timer.h"
#include "console.h"
#include "async.h"
#include <iostream>
#include <windows.h>

using ali::cout;

int main() {
	ali::async<int(std::string&)> x([](std::string& x) -> int {
		return x[0];
		});
	std::string y = "Hekki";
	cout << x(y).await();

	return 0;
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