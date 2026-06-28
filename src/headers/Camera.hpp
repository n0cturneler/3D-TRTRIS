#pragma once

#include "Options.hpp"

#include <raylib.h>

namespace cam
{
	Camera3D initialize();
	Vector3 update(const Vector3& position, float mouseWheelState);

}
