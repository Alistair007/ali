#pragma once
#include <Windows.h>
#include <iostream>
#include "window.h"
//
//namespace cursor {
//	POINT position()
//	{
//		POINT pos;
//		GetCursorPos(&pos);
//		return pos;
//	}
//	//POINT relativePosition(HWND window)
//	//{
//	//	POINT pos = position();
//	//	POINT windowPos = window::position(window);
//	//	POINT ret{ pos.x - windowPos.x, windowPos.y - pos.y };
//	//	return ret;
//	//}
//	void hide()
//	{
//		ShowCursor(FALSE);
//	}
//	void show()
//	{
//		ShowCursor(TRUE);
//	}
//}