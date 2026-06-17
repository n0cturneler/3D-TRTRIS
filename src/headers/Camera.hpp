#pragma once

#include "Options.hpp"

#include <raylib.h>

namespace cam
{
	Camera3D initializeCamera();
	Vector3 updateCamera(const Vector3& position, float mouseWheelState);

}
