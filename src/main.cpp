#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 
	
#include "Options.hpp"
#include "Background.hpp"
#include "Pieces.hpp"
#include "UI.hpp"

#include <raylib.h>
#include <raymath.h>

#include <iostream> 
#include <vector>
#include <cstdint>
#include <print>

int main()
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	// SetConfigFlags(FLAG_FULLSCREEN_MODE);

	InitWindow(0, 0, "3DTRTRIS");
	MaximizeWindow();

	SetTargetFPS(Options::Video::frameTime);

	const int currentMonitor = GetCurrentMonitor();
	const int screenWidth{GetMonitorWidth(currentMonitor)};
	const int screenHeight{GetMonitorHeight(currentMonitor)};

	const Vector3 centerPoint{};
	const Vector3 defaultCamPos{0.0f, Options::Game::camHeight, 1.0f};

	Camera3D camera{};
	camera.position = defaultCamPos;
	camera.target = centerPoint;
	camera.up = {0.0f, 1.0f, 0.0f};
	
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	std::uint64_t currentCycle{};
	float cycleProgress{};
	float tickRate{1.0f / Options::Video::frameTime};

	Piece piece1{{1,2,3}, Piece::Type::I};

	while (!WindowShouldClose())
	{
		float dt{GetFrameTime()};
		cycleProgress += dt;

		if (cycleProgress >= tickRate)
		{
			cycleProgress -= tickRate;
			++currentCycle;
		}

		ClearBackground(BLACK);
		BeginMode3D(camera);

		Background::draw();

		EndMode3D();

		UI::draw();

		EndDrawing();

	}

	CloseWindow();
}
