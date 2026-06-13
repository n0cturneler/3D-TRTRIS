#pragma once

#include <raylib.h>

namespace Options
{
	namespace Video
	{
		inline constexpr int frameTime{120};

	}

	namespace Game
	{
		inline constexpr int rows{20};
		inline constexpr int columns{10};

		inline constexpr int rate{5};

		inline constexpr Vector3 cubeSize{1.75f, 1.75f, 1.75f};
		inline constexpr float camHeight{50.0f};
	}

	namespace Colors
	{
		inline constexpr Color backgroundLines{143, 143, 143, 255};
	}
}
