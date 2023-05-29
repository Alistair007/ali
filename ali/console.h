#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <Windows.h>
#include <vector>
#include "smart_queue.h"
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
						printf(type, a);
				} else
					printf(type, x);
				return;
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value) {
				if constexpr (std::is_array<T>::value) {
					for (const auto& a : x)
					{
						printf(a.c_str());
					}
				}
				else 
					printf(x.c_str());
				return;
			}
			if constexpr (std::is_array<T>::value) {
				for (const auto& a : x)
				{
					printf(type, a);
				}
			}
			else if constexpr (std::is_pointer<T>::value && !std::is_same<T, const char*>::value) { // Deafults "const char*"s to be printed as strings and not as pointers
				printf("%p", x);
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
}
ali::Console console;