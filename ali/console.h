#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <Windows.h>
#include "smart_queue.h"
// Extras

namespace ali{
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
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, float>::value) {
				string y = "%.";
				y += to_string(precision);
				y += "f";
				type = y.c_str();
				printf(type, x);
				return;
			}
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, double>::value) {
				string y = "%.";
				y += to_string(precision);
				y += "f";
				type = y.c_str();
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
			else if constexpr (std::is_pointer<T>::value) {
				printf("%p", x);
			}
			else {
				printf(type, x);
			}
		}
		template<typename T>
		void log(const T& x, size_t font, size_t background = colors::black) {
			SetConsoleTextAttribute(hConsole, background * 16 + font);
			log(x);
			SetConsoleTextAttribute(hConsole, 7);
		}

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
		Console() { };
		~Console() { };
		size_t precision = 4;
	private:
		std::string queue;
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	};

	#define Colors Console::colors
	#define COLOR_ERROR console::colors::black,console::colors::red
	#define COLOR_SUCCESS console::colors::green,console::colors::black
}
ali::Console console;