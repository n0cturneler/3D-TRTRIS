#include "UI.hpp"

#include <raylib.h>

#include <chrono>

void UI::draw()
{
	FPS();
}

void UI::FPS()
{
	DrawFPS(10, 10);
}

void UI::lockDelay(std::chrono::time_point<std::chrono::steady_clock>& lastGravityTick)
{
	
}
