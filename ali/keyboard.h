#pragma once
#include <Windows.h>
#include <thread>
#include <iostream>

namespace keyboard {
	void onKeyPress(char key, void (*func)())
	{
		new std::thread(
			[](char key, void (*func)())
			{
				while (true)
				{
					SHORT keyState = GetKeyState(key);
					bool isToggled = keyState & 1;
					bool isDown = keyState & 0x8000;
					if (isDown || isToggled)
					{
						func();
					}
				}
			},
			key,
			func
		);
	}
}