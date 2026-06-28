#include "Camera.hpp"

#include "Options.hpp"
using namespace options;

#include <raylib.h>

#include <iostream>
#include <algorithm>

namespace cam
{
	Camera3D initialize()
	{
		Camera3D camera{};
		camera.position = game::defaultCamPos;
		camera.target = game::worldOrigin;
		camera.up = game::camUpVector;

		camera.fovy = game::camFOVY;
		camera.projection = game::camProjection;

		return camera;
	}

	Vector3 update(const Vector3& position, float mouseWheelState)
	{
		Vector3 newPosition{position};

		if (mouseWheelState > 0)
		{
			newPosition.y -= game::camScrollRate;
		}
		else if (mouseWheelState < 0)
		{
			newPosition.y += game::camScrollRate;
		}

		newPosition.y = std::clamp(newPosition.y, position.z, 300.0f);

		return newPosition;
	}
}
