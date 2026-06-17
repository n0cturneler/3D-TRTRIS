#pragma once

#include "Options.hpp"
#include "Grid.hpp"

#include <raylib.h>

#include <vector>

namespace cube
{
	struct Cube
	{
		Color m_color{};
		Color m_borderColor{};

		grid::Grid2D m_gridPos{};
	};

	void drawCubes(const std::vector<Cube>& cubes);
}

