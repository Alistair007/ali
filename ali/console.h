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
		template<typename T>
		void log(const T& x) {
			const char* type = "%s";
			if constexpr (std::is_same<std::remove_all_extents_t<T>, char*>::value || std::is_same<std::remove_all_extents_t<T>, const char*>::value)
				type = "%s";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, const wchar_t*>::value)
				type = "%ls";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, char>::value)
				type = "%c";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, int>::value)
				type = "%i";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, unsigned int>::value || std::is_same<std::remove_all_extents_t<T>, size_t>::value)
				type = "%ld";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, const wchar_t*>::value)
				type = "%ls";
			else if (std::is_same<std::remove_all_extents_t<T>, wchar_t>::value) // Currently not working!!!
			{
				if constexpr (std::is_array<T>::value) {
					for (const auto a : x)
						printf("%lc", a);
				}
				else
					printf("%lc", x);
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, long long>::value)
			{
				type = "%lld";
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, float>::value || std::is_same<std::remove_all_extents_t<T>, double>::value) {
				string y = "%.";
				y += to_string(precision);
				y += "f";
				type = y.c_str();
				if constexpr (std::is_array<T>::value)
				{
					for (const auto& a : x)
						log(a);
				} else
					printf(type, x);
				return;
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value) {
				if constexpr (std::is_array<T>::value) {
					for (const auto& a : x)
					{
						log(a.c_str());
					}
				}
				else 
					printf(x.c_str());
				return;
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::wstring>::value) {
				if constexpr (std::is_array<T>::value) {
					for (const auto& a : x)
					{
						log(a.c_str());
					}
				}
				else
					printf("%ls", x.c_str());
				return;
			}
			if constexpr (std::is_array<T>::value) {
				for (const auto& a : x)
				{
					log(a);
				}
			}
			else if constexpr (std::is_pointer<T>::value && !std::is_same<T, const char*>::value && !std::is_same<T, const wchar_t*>::value) { // Deafults "const char*"s to be printed as strings and not as pointers
				printf("%p", x);
			}
			else if constexpr (std::is_same<std::remove_all_extents<T>, bool>::value)
			{
				if constexpr (std::is_array<T>::value){
					for (const auto& a : x)
					{
						log(a);
					}
				}
				else {
					if (x)
						printf("true");
					else
						printf("false");
				}
			}
			else {
				printf(type, x);
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
	
	class vostream
	{
	public:
		vostream() {
			new std::thread(
				[&] {
					Console myConsole;
					while (!terminate)
					{
						if (content.empty())
							continue;
						myConsole.log(content.front());
						content.pop();
					}
				}
			);
		}
		~vostream() {
			terminate = true;
		}
		template <typename T>
		vostream& operator<<(const T& x)
		{
			if constexpr (std::is_same<T, std::string>::value)
				content.push(x);
			else if constexpr (std::is_integral<T>::value) // Idk
				content.push(std::to_string(x));
			else {
				string y = x;
				content.push(y);
			}
			return *this;
		}
	private:
		std::queue<string> content;
		bool terminate = false;
	};

	ostream cout;
	queue qout;
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