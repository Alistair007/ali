#pragma once
#include <stdio.h>
#include <string>
#include <iterator>
#include <type_traits>
#include <Windows.h>
#include <vector>
#include <thread>
// Extras

#define _JAVASCRIPT_STYLE_LOGGING true
#define _EXTRA_DETAIL true
#define _ALL_ALI true

#ifdef _ALL_ALI
#include "async.h"
#endif // _ALL_ALI


#define _ALI_BEGIN namespace ali{
#define _ALI_END }

_ALI_BEGIN

template<typename _Err>
concept is_error_what = requires {
	_Err::what();
};

using namespace std;
class ostream;
class qostream;
class Console {
public:
	// Formatted log
	template <class ... Ts>
	void logf(Ts && ... inputs)
	{
		int i = 0;
		([&]
			{
				i++; // i is the current place
				log(inputs);
			} (), ...);
	}

	// Pretty log
#if _JAVASCRIPT_STYLE_LOGGING
	template<typename T>
	void plog(const T& data, std::string indent = "")
	{
		log(indent);
		if constexpr (std::is_array<T>::value)
		{
			size_t size = sizeof(data) / sizeof(data[0]);
			logf('(', size, ") [");
			if constexpr (is_array_multidimensional<T>::value) {
				log('\n');
				indent += "   ";
			}
			for (size_t i = 0; i < size; i++)
			{
				log(indent);
				plog(data[i]);
				log(", ");
				if constexpr (is_array_multidimensional<T>::value) log('\n');
			}
			log("\b\b]");
		}
		else {
			log(data);
		}
	}
	template<typename T>
	void plog(const std::vector<T>& data, std::string indent = "") // Vectors will wait
	{
		log("Pretty vector logging isn't currently supported!\n", 0, 0, 0, 255, 0, 0);
	}
#else
	template<typename T>
	void plog(const T& data, const char* bef = "[", const char* aft = "] ", const char* end = "\n")
	{
		if constexpr (std::is_array<T>::value) {
			size_t pos = 0;
			string indent = bef;
			indent.insert(indent.begin(), ' ');
			indent.insert(indent.begin(), ' ');
			indent.insert(indent.begin(), ' ');
			for (const auto& x : data) {
				log(bef);
				log(pos);
				log(aft);
				if constexpr (is_array_multidimensional<T>::value)
					log("\n");
				plog(x, indent.c_str());
				if constexpr (!is_array_multidimensional<T>::value)
					log(end);
				pos++;
			}
		}
		else {
			logf(data, '(', typeid(data).name(), ')');
		}
	}
#endif // _JAVASCRIPT_STYLE_LOGGING

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
#if _EXTRA_DETAIL
		if (data == (unsigned long long) - 1) printf("(max unsigned long long)");
		else printf("%zu", data);
#else
		printf("%zu", data);
#endif // _EXTRA_DETAIL
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
	void log(std::string data)
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
#ifdef _ALL_ALI
	//template<typename T>
	//void log(ali::promise<T> data) {
	//	if (data.finished()) {
	//		logf("(promised)", data.get());
	//	} else 
	//	printf("%s%s%c","ali::promise<", typeid(T).name(), '>');
	//}
#endif // _ALL_ALI

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
			log("Unknown type!", 0x0c0c0c, 0xff0000);
		}
	}
	template<typename T>
	void log(const std::vector<T>& vec, size_t font, size_t background = 0x0c0c0c)
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
	void log(const T& text, int fontColorCode, int backgroundColorCode = 0x0c0c0c) {
		printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm", (fontColorCode >> 16) & 0xFF, (fontColorCode >> 8) & 0xFF, fontColorCode & 0xFF, (backgroundColorCode >> 16) & 0xFF, (backgroundColorCode >> 8) & 0xFF, backgroundColorCode & 0xFF);
		log(text);
		printf("\033[0m"); // Reset formatting to default
	}
	template<typename T>
	void log(const T& text, int fontR, int fontG, int fontB, int bgR = 12, int bgG = 12, int bgB = 12) // Suggested, faster than hex
	{
		printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm", fontR & 0xFF, fontG & 0xFF, fontB & 0xFF, bgR & 0xFF, bgG & 0xFF, bgB & 0xFF);
		log(text);
		printf("\033[0m"); // Reset formatting to default
	}

	template<typename T>
	void error(const T& e) {
		log(e, 0, 0, 0, 255, 0, 0);
	}

	template<typename _Err>
	requires is_error_what<_Err>
	void error(const _Err& e) {
		log(e.what(), 0, 0, 0, 255, 0, 0);
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

	static std::string font_color(short r, short g, short b)
	{
		std::string x = "\033[38;2;";
		x += std::to_string(r);
		x += ";";
		x += std::to_string(g);
		x += ";";
		x += std::to_string(b);
		x += "m";
		return x;
	}
	static std::string background_color(short r, short g, short b)
	{
		std::string x = "\033[48;2;";
		x += std::to_string(r);
		x += ";";
		x += std::to_string(g);
		x += ";";
		x += std::to_string(b);
		x += "m";
		return x;
	}
private:
	std::string queue;
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	template <typename T>
	struct is_array_multidimensional
	{
		static constexpr bool value =
			std::is_array<std::remove_extent<T>::type>::value;
	};
	template<typename T>
	static void add(string& s, T adder) {
		if constexpr (is_integral<T>::value) {
			s += to_string(adder);
		}
		else if constexpr (is_floating_point<T>::value) {
			s += to_string(adder);
		}
		else if constexpr (is_same<T, wstring>::value) {
			string conv = string(adder.begin(), adder.end());
			s += conv;
		}
		else if constexpr (is_same<T, const wchar_t*>::value) {
			wstring med = adder;
			string conv = string(med.begin(), med.end());
			s += conv;
		}
		else {
			s += adder;
		}
	}
};

#define Colors Console::colors
#define COLOR_ERROR console::colors::0x0c0c0c,console::colors::0xff0000
#define COLOR_SUCCESS console::colors::green,console::colors::0x0c0c0c
#define FONT_COLOR_COMPTIME(r,g,b) "\033[38;2;" #r ";" #g ";" #b "m"
#define BACKGROUND_COLOR_COMPTIME(r,g,b) "\033[48;2;" #r ";" #g ";" #b "m"

class ostream {
public:
	template<typename T>
	ostream& operator<<(const T& x) {
		myConsole.log(x);
		return *this;
	}
	template<typename T>
	void type(const T& type) {
		myConsole.log(typeid(T).name());
	}
private:
	Console myConsole;
};
class eostream {
public:
	template<typename T>
	eostream& operator<<(const T& x) {
		std::string full = FONT_COLOR_COMPTIME(0, 0, 0) BACKGROUND_COLOR_COMPTIME(255, 0, 0);
		full += x;
		full += "\033[0m";
		myConsole.log(full.c_str());
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
eostream cerr;
qostream qout;

void fprint(const char* text)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD bytesWritten;

	WriteFile(consoleHandle, text, static_cast<DWORD>(strlen(text)), &bytesWritten, nullptr);
}
_ALI_END
ali::Console console;

#if _JAVASCRIPT_STYLE_LOGGING
template<typename T>
void fplog_helper(const char* name, const T& data)
{
	ali::Console myConsole;
	if constexpr (!std::is_array<T>::value)
		myConsole.logf(FONT_COLOR_COMPTIME(0, 255, 0), typeid(T).name(), ' ', name, FONT_COLOR_COMPTIME(0xcc, 0xcc, 0xcc), " = ", data, '\n');
	else {
		myConsole.logf(FONT_COLOR_COMPTIME(0, 255, 0), typeid(T).name(), ' ', name, FONT_COLOR_COMPTIME(0xcc, 0xcc, 0xcc), ": \n"); // Idk if i want to keep \n\n or just put \n...
		myConsole.plog(data);
		myConsole.log('\n');
	}
}
#else
template<typename T>
void fplog_helper(const char* name, const T& data)
{
	ali::Console myConsole;
	if constexpr (!std::is_array<T>::value)
		myConsole.logf(FONT_COLOR_COMPTIME(0, 255, 0), typeid(T).name(), ' ', name, FONT_COLOR_COMPTIME(0xcc, 0xcc, 0xcc), " = ", data);
	else {
		myConsole.logf(FONT_COLOR_COMPTIME(0, 255, 0), typeid(T).name(), ' ', name, FONT_COLOR_COMPTIME(0xcc, 0xcc, 0xcc), ": \n"); // Idk if i want to keep \n\n or just put \n...
		myConsole.plog(data, "   [");
	}
}
#endif // _JAVASCRIPT_STYLE_LOGGING

void fplog_helper(const char* name, const std::string& str)
{
	ali::Console myConsole;
	myConsole.logf("std::string ", name, " = ", str, "\n    .length() = ", str.length());
}


#define fplog(data) fplog_helper(#data, std::cref(data).get())

//																	   lol replacer
// Discarded section: I either can't get these things to work or i'm ti0xff0000 of doing them.

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