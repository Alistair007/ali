#include "timer.h"
#include "console.h"
#include "testingVec.h"
#include <iostream>
#include <windows.h>

using ali::cout;

template<typename T>
void logTv(const tv<T>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		console.logf(i, ": ", v[i], '\n');
	}
}

inline unsigned short f_getBaseByIndex(size_t index) {
	return log2_64_f(index + 2) - 1;
}

inline unsigned short f_getIndexByIndex(size_t index) {
	return index - (1ULL << (log2_64_f(index + 2))) + 2;
}

int main() {
	tv<int> x;
	
	x += 123;

	x += 1233;

	x += 32;

	x--;
	x--;
	x--;

	logTv(x);

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