#pragma once

#include "Options.hpp"
#include "Grid.hpp"
#include "PieceType.hpp"

#include <raylib.h>

#include <vector>

namespace cell
{
	struct Cell
	{
		PieceType type{PieceType::none};
	};

	void drawCell(const std::vector<Cell>& cubes);
}

