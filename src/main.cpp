#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 

#include "Options.hpp"
#include "Background.hpp"
#include "PieceType.hpp"
#include "Pieces.hpp"
#include "Camera.hpp"
#include "UI.hpp"
#include "Cell.hpp"

#include <raylib.h>

#include <imgui.h>

#include <iostream> 
#include <vector>
#include <cstdint>
#include <print>
#include <chrono>
#include <random>

int main()
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	// SetConfigFlags(FLAG_FULLSCREEN_MODE);

	InitWindow(0, 0, "3DTRTRIS");
	MaximizeWindow();

	SetTargetFPS(options::video::frameRate);

	[[maybe_unused]] const int currentMonitor = GetCurrentMonitor();
	[[maybe_unused]] const int screenWidth{GetMonitorWidth(currentMonitor)};
	[[maybe_unused]] const int screenHeight{GetMonitorHeight(currentMonitor)};

	Camera3D camera{cam::initializeCamera()};

	std::array<PieceType, 7> currentBag;
	piece::Piece activePiece{options::game::gridSpawn, piece::getNextType()};

	using Board = std::array<
		std::array<cell::Cell, options::game::columns>,
		options::game::rows
	>;

	Board staticPieces{};

	std::chrono::time_point<std::chrono::steady_clock> lastGravityTick{std::chrono::steady_clock::now()};

	while (!WindowShouldClose())
	{
		[[maybe_unused]] float dt{GetFrameTime()};

		float mouseWheelMovement = GetMouseWheelMove();
		camera.position = cam::updateCamera(camera.position, mouseWheelMovement);

		input::PieceActions currentAction{input::getPieceAction()};
		activePiece.update(currentAction, lastGravityTick, staticPieces);

		ClearBackground(options::colors::background);
		BeginMode3D(camera);

		Background::draw();

		piece::drawStatic(staticPieces);
		activePiece.draw();

		EndMode3D();

		UI::draw();

		EndDrawing();
	}

	CloseWindow();
}
