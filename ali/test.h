#pragma once
#include <math.h>
#include <Windows.h>

int digit(int a, int b) {
	return a / (int)pow(10, b - 1) % 10;
}
char* font_color(short r, short g, short b) {
	short colorLength = log10(r) + log10(g) + log10(b);
	char* ret = new char[11 + colorLength];
	ret[0] = '\033';
	ret[1] = '[';
	ret[2] = '3';
	ret[3] = '8';
	ret[4] = ';';
	ret[5] = '2';
	ret[6] = ';';
	for (size_t i = 1; i < log10(r) + 1; i++)
	{
		ret[7 + (int)log10(r) - i] = digit(r, i) + 48;
	}
	for (size_t i = 1; i < log10(g) + 1; i++)
	{
		ret[7 + (int)log10(g) - i] = digit(g, i) + 48;
	}
	for (size_t i = 1; i < log10(b) + 1; i++)
	{
		ret[7 + (int)log10(b) - i] = digit(b, i) + 48;
	}
	return ret;
}

template<typename Func>
void repeat_delay(Func f, int n, int t_ms) {
	for (size_t i = 0; i < n; i++)
	{
		f();
		Sleep(t_ms);
	}
}