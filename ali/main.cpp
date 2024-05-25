#include "timer.h"
#include "console.h"
#include "testingVec.h"
#include <iostream>
#include <windows.h>

using ali::cout;

template<typename T>
void printTv(const tv<T>& v) {
	cout << "size: " << v.s_size << "\ncapacity: " << v.s_capacity << "\ncurrentPtr: " << v.s_currentPtr << "\ncurrentPtrSize: " << v.s_currentPtrSize << "\nptrs[0][0]: " << v.ptrs[0][0];
}

template<typename T>
void printTvData(const tv<T>& v) {
	size_t capacity = 2;
	size_t point = 0;
	for (size_t i = 0; i <= v.s_currentPtr; i++)
	{
		for (size_t k = 0; k < capacity; k++) {
			cout << i << ' ' << k << ": " << v.ptrs[i][k] << '\n';
			point++;
			if (point == v.s_size) break;
		}
		capacity *= 2;
	}
}

int main() {
	tv<int> x;
	for (size_t i = 0; i < 10000; i++)
		x.push_back(i);

	/*printTvData(x);*/

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