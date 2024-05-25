#pragma once
#include <string>
#include <type_traits>
#define _ALI_BEGIN namespace ali{
#define _ALI_END }

_ALI_BEGIN

using namespace std;
namespace str {
	template<typename T>
	void add(string& s, T adder) {
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
	template<typename T>
		void to_string(const T& s) {
		if constexpr (is_integral<T>::value) {
			return to_string(s);
		}
		else if constexpr (is_same<T, wstring>::value) {
			string conv = string(s.begin(), s.end());
			return conv;
		}
		else if constexpr (is_same<T, const wchar_t*>::value) {
			wstring med = s;
			string conv = string(med.begin(), med.end());
			return conv;
		}
		else {
			return s;
		}
	}
}

template <class ... Ts>
void flogf(Ts && ... inputs) // Suggested. Faster but may interfere with the queue
{
	string pr = "";
	([&]
		{
			i++; // i is the current place
			str::add(pr, inputs);
		} (), ...);
	printf(pr.c_str());
}

_ALI_END