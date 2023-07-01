#pragma once
#include <string>
#include <Windows.h>
namespace ali {
	using namespace std;
	namespace raw {
		HWND g_HWND = NULL;
		BOOL CALLBACK EnumWIndowsFunc(HWND hwnd, LPARAM lParam) {
			DWORD lpdwProcessId;
			GetWindowThreadProcessId(hwnd, &lpdwProcessId);
			if (lpdwProcessId == lParam)
			{
				g_HWND = hwnd;
				return FALSE;
			}
			return TRUE;
		}
	}
	void convert(DWORD pid, HWND& hwnd)
	{
		EnumWindows(raw::EnumWIndowsFunc, pid);
		hwnd = raw::g_HWND;
	}
	void convert(HANDLE handle, HWND& hwnd)
	{
		DWORD pid = GetProcessId(handle);
		EnumWindows(raw::EnumWIndowsFunc, pid);
		hwnd = raw::g_HWND;
	}
	void convert(HANDLE handle, DWORD& pid)
	{
		pid = GetProcessId(handle);
	}
	void convert(DWORD pid, HANDLE& handle, DWORD desiredAccess = PROCESS_ALL_ACCESS, BOOL inheritHandle = FALSE)
	{
		handle = OpenProcess(desiredAccess, inheritHandle, pid);
	}
	void convert(HWND hwnd, DWORD& pid)
	{
		pid = GetWindowThreadProcessId(hwnd, NULL);
	}
	void convert(HWND hwnd, HANDLE& handle, DWORD desiredAccess = PROCESS_ALL_ACCESS, BOOL inheritHandle = FALSE)
	{
		DWORD pid = GetWindowThreadProcessId(hwnd, NULL);
		handle = OpenProcess(desiredAccess, inheritHandle, pid);
	}


	void convert(wstring wstr, string& str)
	{
		str = string(wstr.begin(), wstr.end());
	}
	void convert(string str, wstring& wstr) {
		wstr = wstring(str.begin(), str.end());
	}


	void convert(string str, HWND& hwnd) //String interpreted as pid!
	{
		convert(stoi(str), hwnd);
	}
	void convert(string str, DWORD& pid) //String interpreted as pid!
	{
		pid = stoi(str);
	}
	void convert(string str, HWND& hwnd) //String interpreted as pid!
	{
		convert(stoi(str), hwnd);
	}
}