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
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, unsigned int>::value || std::is_same<std::remove_all_extents_t<T>, size_t>::value)
				type = "%f";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value) {
				printf(x.c_str());
				return;
			}
			if constexpr (!std::is_array<T>::value) {
				printf(type, x);
			}
			else {
				for (const auto& a : x)
				{
					printf(type, a);
				}
			}
		}
		template<typename T>
		void log(const T& x, size_t font, size_t background = colors::black) {
			const char* type = "%s";
			SetConsoleTextAttribute(hConsole, background * 16 + font);
			if constexpr (std::is_same<std::remove_all_extents_t<T>, char*>::value || std::is_same<std::remove_all_extents_t<T>, const char*>::value)
				type = "%s";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, char>::value)
				type = "%c";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, int>::value)
				type = "%i";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, unsigned int>::value || std::is_same<std::remove_all_extents_t<T>, size_t>::value)
				type = "%ld";
			else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value) {
				printf(x.c_str());
				return;
			}
			if constexpr (!std::is_array<T>::value) {
				printf(type, x);
			}
			else {
				if constexpr (std::is_same<std::remove_all_extents_t<T>, char*>::value || std::is_same<std::remove_all_extents_t<T>, const char*>::value)
					type = "%s";
				else if constexpr (std::is_same<std::remove_all_extents_t<T>, char>::value)
					type = "%c";
				else if constexpr (std::is_same<std::remove_all_extents_t<T>, int>::value)
					type = "%i";
				else if constexpr (std::is_same<std::remove_all_extents_t<T>, unsigned int>::value || std::is_same<std::remove_all_extents_t<T>, size_t>::value)
					type = "%ld";
				else if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value) {
					printf(x.c_str());
					return;
				}
				for (const auto& a : x)
				{
					printf(type, a);
				}
			}
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
	private:
		std::string queue;
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	};

	Console console;

	#define Colors Console::colors
	#define COLOR_ERROR console::colors::black,console::colors::red
	#define COLOR_SUCCESS console::colors::green,console::colors::black
}