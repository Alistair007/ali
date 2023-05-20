#pragma once
#include <string>
#include <codecvt>
#include <locale>
#pragma warning(disable: 4996)
namespace ali {
	namespace convert {
		using namespace std;
		using convert_t = codecvt_utf8<wchar_t>;
		wstring_convert<convert_t, wchar_t> strconverter;

		string to_str(wstring wstr)
		{
			return string(wstr.begin(), wstr.end());
		}

		wstring to_wstr(string str)
		{
			return wstring(str.begin(), str.end());
		}
	}
}