#include "UI.hpp"

#include <raylib.h>

void UI::draw()
{
	FPS();
	lockDelay();
}

void UI::FPS()
{
	DrawFPS(10, 10);
}

void UI::lockDelay()
{
	
}
