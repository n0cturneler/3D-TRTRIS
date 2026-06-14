#pragma once

#include "Grid.hpp"
#include "Options.hpp"

#include <raylib.h>

#include <iostream> 
#include <vector>
#include <array>
#include <cstdint>

namespace PieceData
{	
	using Grid2D = Grid::Grid2D;
	using PieceOffset = std::array<Grid2D, 4>;
	using PieceRotations = std::array<PieceOffset, 4>;
	using Pieces = std::array<PieceRotations, 7>;

	inline constexpr PieceRotations T_Piece{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{-1, 0},
			Grid2D{0, -1}
		},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{0, 1},
			Grid2D{0, -1}
		},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{-1, 0},
			Grid2D{0, 1}
		},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{0, 1},
			Grid2D{0, -1}
		}
	};

	inline constexpr Pieces Data
	{
		T_Piece,
	};

}

namespace Input
{
	struct Actions
	{
		bool movLeft{};
		bool movRight{};

		bool rotLeft{};
		bool rotRight{};
		bool rot180{};

		bool softDrop{};
		bool hardDrop{};
	};

	Actions getAction();
}


class Piece
{
public:
	enum class Type { T };

	Piece(Grid::Grid2D spawnPos, Type type, int rotationState = 0);

	void updatePiece(const Input::Actions& actions, const std::uint64_t& currentCycle);
	void drawPiece() const;

private:
	Grid::Grid2D m_gridPos{0, 0};

	Type m_type{};
	int m_rotationState{};
};
