#pragma once
#include <Windows.h>

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

class Window // TODO: Major structure reworking
{
public:
	/*
		Idk what interesting things to add. Any comment?
	*/
	template<typename T>
	Window(const T& templateData) {
		convert(templateData, this->hwnd);
	}
	
	~Window(){}

	RECT rect()
	{
		RECT ret;
		GetWindowRect(hwnd, &ret);
		return ret;
	}

	POINT centerPos()
	{
		return { size().x/2, size().y/2 };
	}

	POINT size()
	{
		POINT pnt{ rect().right - rect().left, rect().bottom - rect().top };
		return pnt;
	}

	POINT getRelativeMousePos() // The coordinates relative to the window's bottom left corner
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		POINT ret{ mousePos.x - rect().left, rect().bottom - mousePos.y };
		return ret;
	}

	void setRelativeMousePos(int x, int y){
		SetCursorPos(rect().left + x, rect().bottom - y);
	}

	void setRelativeMousePos(const POINT& pos) {
		SetCursorPos(rect().left + pos.x, rect().bottom - pos.y);
	}

	const char* name()
	{
		LPTSTR n { 0 };
		GetClassName(hwnd, n, 256); // 256?
	}
private:
	HWND hwnd;
};

Window thisWindow(GetConsoleWindow());

//int length = GetWindowTextLength(hWnd);
//wchar_t* buffer = new wchar_t[length + 1];
//GetWindowText(hWnd, buffer, length + 1);
//std::wstring windowTitle1(buffer);
//std::string windowTitle(windowTitle1.begin(), windowTitle1.end());
//delete[] buffer;
//
// List visible windows with a non-empty title
//if (IsWindowVisible(hWnd) && length != 0) {
//	std::cout << hWnd << ":  " << windowTitle << std::endl;
//}
//return TRUE;