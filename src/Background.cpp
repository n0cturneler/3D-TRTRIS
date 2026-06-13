#include "Background.hpp"

#include <raylib.h>
#include <raymath.h>

#include "Options.hpp"

#include <print>

using namespace Options;

namespace Background
{
	void draw()
	{		
		//Clean this dogshit up
		for (int i{0}; i <= Game::columns; i++)
		{
			Vector3 startPos{(Game::cubeSize.x * i) - (Game::cubeSize.x * Game::columns) / 2, 0.0f, +(Game::cubeSize.z * Game::rows) / 2};
			Vector3 endPos{(Game::cubeSize.x * i) - (Game::cubeSize.x * Game::columns) / 2, 0.0f, -(Game::cubeSize.z * Game::rows) / 2};
			DrawLine3D(startPos, endPos, Colors::backgroundLines);
		}

		for (int i{0}; i <= Game::rows; i++)
		{
			Vector3 startPos{+(Game::cubeSize.x * Game::columns) / 2, 0.0f, (Game::cubeSize.z * i) - (Game::cubeSize.x * Game::rows) / 2};
			Vector3 endPos{-(Game::cubeSize.x * Game::columns) / 2, 0.0f, (Game::cubeSize.z * i) - (Game::cubeSize.x * Game::rows) / 2};
			DrawLine3D(startPos, endPos, Colors::backgroundLines);
		}

	}
}
