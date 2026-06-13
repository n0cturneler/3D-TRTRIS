#pragma once

#include <raylib.h>

#include <array>

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

		inline constexpr int DAS{20}; // in ms
		inline constexpr int ARR{20}; // in ms
	}

	namespace Colors
	{
		inline constexpr Color backgroundLines{143, 143, 143, 255};

		//PIECES

		inline constexpr std::array<Color, 7> pieceColors = {
			Color{160, 0, 240, 255}, // T
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255}
		};

		inline constexpr std::array<Color, 7> pieceBorderColors = {
			Color{100, 0, 180, 255}, // T
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
		};
	}
}
