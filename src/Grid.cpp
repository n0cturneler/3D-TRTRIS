#include "Grid.hpp"

#include "Options.hpp"
using namespace options;

#include <raylib.h>

grid::Grid2D grid::add(Grid2D grid1, Grid2D grid2)
{
	return {grid1.x + grid2.x, grid1.y + grid2.y};
}

grid::Grid2D grid::inverse(Grid2D grid)
{
	return {grid.x * -1, grid.y * -1};
}

Vector3 grid::gridToWorld(grid::Grid2D gridPos)
{
	return {game::gridOrigin.x + (static_cast<float>(gridPos.x) * game::cubeSize.x),
		game::gridOrigin.y,
		game::gridOrigin.z + (static_cast<float>(gridPos.y) * game::cubeSize.z)};
}


