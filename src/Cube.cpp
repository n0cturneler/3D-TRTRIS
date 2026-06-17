#include "Cube.hpp"

#include "Options.hpp"
using namespace options;

#include "Grid.hpp"

#include <raylib.h>

#include <vector>

void cube::drawCubes(const std::vector<cube::Cube>& cubes)
{
	for (const Cube& cube : cubes)
	{	
		Vector3 position{grid::gridToWorld(cube.m_gridPos)};
		DrawCube(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, cube.m_color);
		DrawCubeWires(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, cube.m_borderColor);
	}
}
