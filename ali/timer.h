#pragma once
#include <chrono>

//#define milliseconds std::chrono::milliseconds;
//#define seconds std::chrono::seconds;
//#define minutes std::chrono::minutes;
//#define hours std::chrono::milliseconds;

namespace ali {
	using namespace std::chrono;
	class Timer
	{
	public:
		Timer() {
			begin = high_resolution_clock::now();
		}
		~Timer() {

		}
		template<typename T>
		auto time_passed()
		{
			return duration_cast<T>(end - high_resolution_clock::now());
		}

		template<typename T>
		auto get_time()
		{
			auto x = duration_cast<T>(end - begin);
			return x;
		}

		void stop() {
			end = high_resolution_clock::now();
		}

	private:
		steady_clock::time_point begin;
		steady_clock::time_point end;
	};
}