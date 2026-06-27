#pragma once

#include <raylib.h>

#include <chrono>

namespace UI
{	
	void draw();

	void FPS();
	void lockDelay(std::chrono::time_point<std::chrono::steady_clock>& lastGravityTick);

}
