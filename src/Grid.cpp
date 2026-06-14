#include "Grid.hpp"

#include "Options.hpp"
using namespace Options;

#include <raylib.h>

Grid::Grid2D Grid::add(Grid2D grid1, Grid2D grid2)
{
	return {grid1.x + grid2.x, grid1.y + grid2.y};
}

Vector3 Grid::gridToWorld(Grid::Grid2D gridPos)
{
	return {Game::gridOrigin.x + (static_cast<float>(gridPos.x) * Game::cubeSize.x),
		Game::gridOrigin.y,
		Game::gridOrigin.z + (static_cast<float>(gridPos.y) * Game::cubeSize.z)};
}
