#pragma once

#include "Grid.hpp"
#include <raylib.h>

#include <array>
#include <chrono>

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

		inline constexpr int gravityMS{1000}; // in ms
		inline constexpr int DAS{166}; // in ms
		inline constexpr int ARR{33}; // in ms
		
		//Camera
		inline constexpr float camScrollRate{5.0f};
		inline constexpr float camFOVY{45.0f};

		inline constexpr Vector3 defaultCamPos{0.0f, 44.0f, 0.01f};
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
		inline constexpr Color backgroundLines{100, 100, 100, 255};
		inline constexpr Color backgroundBufferLines{50, 50, 50, 255};

		//PIECES

		inline constexpr Color T{200, 70, 255, 255};
		inline constexpr Color T_Border{120, 10, 175, 255};

		inline constexpr Color Z{255, 40, 50, 255};
		inline constexpr Color Z_Border{140, 20, 30, 255};

		inline constexpr std::array<Color, 7> pieceColors = {
			T, 
			Z,
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255},
			Color{160, 0, 240, 255}
		};

		inline constexpr std::array<Color, 7> pieceBorderColors = {
			T_Border, 
			Z_Border,
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
			Color{100, 0, 180, 255},
		};
	}
}
