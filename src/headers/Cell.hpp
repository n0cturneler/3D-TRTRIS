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
		pieceType::PieceType type{pieceType::PieceType::none};
	};
}

