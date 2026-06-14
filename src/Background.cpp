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
		// Buffer Grid
		for (int i{0}; i <= Game::bufferRows; i++)
		{
			float zPos{Game::cubeSize.z * i};

			Vector3 startPos{Game::halfWidth, 0.0f, zPos - Game::fullHeight - Game::halfHeight};
			Vector3 endPos{-Game::halfWidth, 0.0f, zPos - Game::fullHeight - Game::halfHeight};

			DrawLine3D(startPos, endPos, Colors::backgroundBufferLines);
		}

		for (int i{0}; i <= Game::columns; i++)
		{
			float xPos{Game::cubeSize.x * i};

			Vector3 startPos{xPos - Game::halfWidth, 0.0f, -Game::fullHeight + Game::halfHeight};
			Vector3 endPos{xPos - Game::halfWidth, 0.0f, -Game::fullHeight - Game::halfHeight};

			DrawLine3D(startPos, endPos, Colors::backgroundBufferLines);
		}

		// Play Grid
		for (int i{0}; i <= Game::columns; i++)
		{
			float xPos{Game::cubeSize.x * i};

			Vector3 startPos{xPos - Game::halfWidth, 0.0f, Game::halfHeight};
			Vector3 endPos{xPos - Game::halfWidth, 0.0f, -Game::halfHeight};

			DrawLine3D(startPos, endPos, Colors::backgroundLines);
		}

		for (int i{0}; i <= Game::rows; i++)
		{
			float zPos{Game::cubeSize.z * i};

			Vector3 startPos{Game::halfWidth, 0.0f, zPos - Game::halfHeight};
			Vector3 endPos{-Game::halfWidth, 0.0f, zPos - Game::halfHeight};

			DrawLine3D(startPos, endPos, Colors::backgroundLines);
		}
	}
}
