#pragma once

#include "Grid.hpp"
#include <raylib.h>

#include <array>

namespace options
{
	namespace video
	{
		inline constexpr int frameRate{120};
	}

	namespace game
	{
		//Game
		inline constexpr int rows{20};
		inline constexpr int columns{10};

		inline constexpr int bufferRows{20};

		// All of these 5 are in milliseconds(ms)
		inline constexpr int gravityMS{2000}; 
		inline constexpr int DAS{166}; 
		inline constexpr int ARR{33}; 
		inline constexpr int lockDelayMS{1500}; 
		inline constexpr int softdropMS{60}; 

		//Camera
		inline constexpr float camScrollRate{5.0f};
		inline constexpr float camFOVY{45.0f};

		inline constexpr Vector3 defaultCamPos{0.0f, 55.0f, 0.01f};
		inline constexpr Vector3 camUpVector{0.0f, 1.0f, 0.0f};
		inline constexpr CameraProjection camProjection{CAMERA_PERSPECTIVE};

		//Cube
		inline constexpr Vector3 cubeSize{1.75f, 1.75f, 1.75f};
		inline constexpr Vector3 halfCube{cubeSize.x * 0.5f, cubeSize.y * 0.5f, cubeSize.z * 0.5f};

		//World
		inline constexpr Vector3 worldOrigin{0.0f, 0.0f, 0.0f};

		inline constexpr float fullHeight{cubeSize.z * rows};
		inline constexpr float halfHeight{(cubeSize.z * rows) * 0.5f};
		inline constexpr float halfWidth{(cubeSize.x * columns) * 0.5f};

		//Grid
		inline constexpr Vector3 gridOrigin{worldOrigin.x + halfCube.x - halfWidth, halfCube.y, worldOrigin.z - halfHeight + halfCube.z};
		inline constexpr grid::Grid2D gridSpawn{4, 0};

	}

	namespace colors
	{
		inline constexpr Color background{0, 0, 0, 255};

		inline constexpr Color backgroundLines{100, 100, 100, 255};
		inline constexpr Color backgroundBufferLines{50, 50, 50, 255};

		//PIECES
		inline constexpr Color I{5, 255, 205, 255};
		inline constexpr Color I_Border{0, 80, 60, 255};

		inline constexpr Color J{15, 30, 255, 255};
		inline constexpr Color J_Border{15, 40, 80, 255};

		inline constexpr Color L{255, 170, 25, 255};
		inline constexpr Color L_Border{80, 30, 5, 255};

		inline constexpr Color O{255, 255, 45, 255};
		inline constexpr Color O_Border{80, 80, 20, 255};

		inline constexpr Color S{55, 255, 8, 255};
		inline constexpr Color S_Border{55, 50, 8, 255};

		inline constexpr Color T{200, 70, 255, 255};
		inline constexpr Color T_Border{120, 10, 175, 255};

		inline constexpr Color Z{255, 40, 50, 255};
		inline constexpr Color Z_Border{140, 20, 30, 255};

		inline constexpr std::array<Color, 7> piece = {
			I,
			J,
			L,
			O,
			S,
			T,
			Z
		};

		inline constexpr std::array<Color, 7> pieceBorder = {
			I_Border,
			J_Border,
			L_Border,
			O_Border,
			S_Border,
			T_Border,
			Z_Border
		};
	}
}
