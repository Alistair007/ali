#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <Windows.h>
#include <vector>
#include "queue.h"
#include <thread>
// Extras

namespace ali{
	using namespace std;
	class Console {
	public:
		class smart_queue;

		static enum colors {
			black = 0,
			electric = 1,
			leaf = 2,
			lightblue = 3,
			red = 4,
			darkpurple = 5,
			gold = 6,
			lightgrey = 7,
			grey = 8,
			blue = 9,
			green = 10,
			aqua = 11,
			lightred = 12,
			purple = 13,
			yellow = 14,
			white = 15,
		};

		// Formatted log section
		template <class ... Ts>
		void logf(Ts && ... inputs)
		{
			int i = 0;
			([&]
				{
					++i; // i is the current place
					log(inputs);
				} (), ...);
		}

		// Formatted log section -- Isn't same as formatted log!
		template<typename T>
		void flog(const std::vector<T>& data, const char* bef = "[", const char* aft = "]: ", const char* end = "\n")
		{
			size_t pos = 0;
			for (size_t i = 0; i < data.size(); i++) {
				logf(bef, pos, aft, data[i], end);
				pos++;
			}
		}
		
		template<typename T>
		void flog(const T& data, const char* bef = "[", const char* aft = "]: ", const char* end = "\n")
		{
			if constexpr (std::is_array<T>::value) {
				size_t pos = 0;
				for (const auto& x : data) {
					logf(bef, pos, aft, x, end);
					pos++;
				}
			}
			else if constexpr (std::is_same<T, std::vector<T::value_type>>) {

			}
			else {
				log("flog - error 01: input isn't an array!\n", red, black);
			}
		}

		// Normal log section
		void log(const char* data)
		{
			printf(data);
		}
		void log(char* data)
		{
			printf(data);
		}
		void log(const char& value)
		{
			printf("%c", value);
		}
		void log(const int& data)
		{
			printf("%d", data);
		}
		void log(const unsigned int& data)
		{
			printf("%ld", data);
		}
		void log(const size_t& data)
		{
			printf("%ld", data);
		}
		void log(const wchar_t* data)
		{
			printf("%ls", data);
		}
		void log(const long long& data)
		{
			printf("%lld", data);
		}
		void log(const float& data)
		{
			string x = "%.";
			x += to_string(precision);
			x += "f";
			printf(x.c_str(), data);
		}
		void log(const std::string& data)
		{
			printf(data.c_str());
		}
		void log(const std::wstring& data)
		{
			printf("%ls", data.c_str());
		}
		void log(const bool& data)
		{
			if (data)
			{
				printf("true");
				return;
			}
			printf("false");
		}

		template<typename T>
		void log(const T& x) {
			if constexpr (std::is_array<T>::value) {
				for (const auto& a : x)
				{
					log(a);
				}
			}
			else if constexpr (std::is_pointer<T>::value && !std::is_same<T, const char*>::value && !std::is_same<T, const wchar_t*>::value) { // Deafults "const char*"s to be printed as strings and not as pointers
				printf("%p", x);
			}
			else {
				log("Unknown type!", black, red);
			}
		}
		template<typename T>
		void log(const std::vector<T>& vec, size_t font, size_t background = colors::black)
		{
			for (size_t i = 0; i < vec.size(); i++)
			{
				log(vec[i], font, background);
			}
		}
		template<typename T>
		void log(const std::vector<T>& vec)
		{
			for (size_t i = 0; i < vec.size(); i++)
			{
				log(vec[i]);
			}
		}
		template<typename T>
		void log(const T& x, size_t font, size_t background = colors::black) {
			SetConsoleTextAttribute(hConsole, background * 16 + font);
			log(x);
			SetConsoleTextAttribute(hConsole, 7);
		}

		// Queue section
		template<typename T>
		void enqueue(const T& data) {
			if constexpr (!std::is_array<T>::value) {
				if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value)
					queue += data;
				else {
					queue += std::to_string(data);
				}
				if (queue.length() >= 4096)
					dequeue();
			}
			else {
				throw std::exception("Array at print enqueuing! Only primitives are allowed!");
			}
		}
		template<typename T>
		void enqueue_m(const T& data) {
			if constexpr (!std::is_array<T>::value) {
				if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value)
					queue += data;
				else {
					queue += std::to_string(data);
				}
			}
			else {
				throw std::exception("Array at print enqueuing! Only primitives are allowed!");
			}
		}
		void dequeue() {
			log(queue);
			queue.clear();
		}

		// Constructors
		Console() { };
		~Console() { };
		size_t precision = 6;
	private:
		std::string queue;
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	};

	#define Colors Console::colors
	#define COLOR_ERROR console::colors::black,console::colors::red
	#define COLOR_SUCCESS console::colors::green,console::colors::black

	class ostream {
	public:
		template<typename T>
		ostream& operator<<(const T& x) {
			myConsole.log(x);
			return *this;
		}
	private:
		Console myConsole;
	};
	class qostream
	{
	public:
		~qostream() {
			myConsole.dequeue();
		}
		template<typename T>
		qostream& operator<<(const T& x) {
			myConsole.enqueue(x);
			return *this;
		}
		void operator--()
		{
			myConsole.dequeue();
		}
		qostream& operator--(int x)
		{
			myConsole.dequeue();
			return *this;
		}
	private:
		Console myConsole;
	};

	ostream cout;
	qostream qout;
}
ali::Console console;




// Discarded section: I either can't get these things to work or i'm tired of doing them.

//class vostream
//{
//public:
//	vostream() {
//		new thread(
//			[&] {
//				while (!done)
//				{
//					if (toPrint.empty()) {
//						if (toKill) done = true;
//						else continue;
//					}
//					if (!toPrint.empty())
//						myConsole.log(toPrint.front());
//					toPrint.pop();
//				}
//				printf("Finished thread!\n");
//			}
//		);
//	}
//	~vostream() {
//		// Should make this turnable off
//		printf("Attempting to delete!\n");
//		toKill = true;
//		while (true)
//		{
//			if (toPrint.empty() && !done)
//				break;
//			// Wait
//		}
//		printf("Deleted vostream!\n");
//	}
//	vostream& operator<<(std::string data)
//	{
//		toPrint.push(data);
//	}
//private:
//	queue<std::string> toPrint;
//	bool done = false;
//	bool toKill = false;
//	Console myConsole;
//};