#include "console.h"
#include "colors.h"
#include "timer.h"

#include <iostream>

int main()
{
	const size_t times = 10000;
	ali::Timer rb;
	for (size_t i = 0; i < times; i++)
	{
		console.log(i, 255, 0, 0);
	}
	rb.stop();
	ali::Timer hx;
	for (size_t i = 0; i < times; i++)
	{
		console.log(i, 0xff0000);
	}
	hx.stop();
	ali::cout << "\nHEX: " << hx.get_time<ali::milliseconds>().count() << "\nRGB: " << rb.get_time<ali::milliseconds>().count();
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