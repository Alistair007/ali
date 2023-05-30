#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include "window.h"

namespace cursor {
	POINT position()
	{
		POINT pos;
		GetCursorPos(&pos);
		return pos;
	}
	//POINT relativePosition(HWND window)
	//{
	//	POINT pos = position();
	//	POINT windowPos = window::position(window);
	//	POINT ret{ pos.x - windowPos.x, windowPos.y - pos.y };
	//	return ret;
	//}
	void onMove(void (*func)())
	{
		new std::thread(
			[](void (*func)()) {
				POINT pos = {0, 0};
				while (true)
				{
					POINT newPoint = position();
					if (pos.x != newPoint.x || pos.y != newPoint.y)
						func();
					pos = position();
				}
			},
			func
		);
	}
	void hide()
	{
		ShowCursor(FALSE);
	}
	void show()
	{
		ShowCursor(TRUE);
	}
	bool posIsSame(POINT one, POINT two)
	{
		return one.x - two.x && one.y - two.y;
	}
}