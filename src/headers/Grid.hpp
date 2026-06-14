#pragma once

#include <raylib.h>

namespace Grid
{
	struct Grid2D
	{
		int x{};
		int y{};
	};

	Vector3 gridToWorld(Grid2D gridPos);
	Grid2D add(Grid2D grid1, Grid2D grid2);
}
