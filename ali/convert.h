#pragma once
#include <string>
namespace ali {
	namespace convert {
		using namespace std;

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