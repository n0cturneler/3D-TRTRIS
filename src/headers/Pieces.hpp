#pragma once

#include "Grid.hpp"
#include "Options.hpp"
#include "PieceType.hpp"
#include "Cell.hpp"

#include <raylib.h>

#include <iostream> 
#include <vector>
#include <array>
#include <chrono>

namespace pieceData
{
	using Grid2D = grid::Grid2D;
	using PieceOffset = std::array<Grid2D, 4>;
	using PieceRotations = std::array<PieceOffset, 4>;
	using Pieces = std::array<PieceRotations, 8>;

	// {1, 1} move towards bottom right 
	// {-1, -1} towards top left

	inline constexpr PieceRotations I{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{1, 0},
			Grid2D{2, 0}
	},
		PieceOffset{
			Grid2D{1, 0},
			Grid2D{1, -1},
			Grid2D{1, 1},
			Grid2D{1, 2}
	},
		PieceOffset{
			Grid2D{0, 1},
			Grid2D{-1, 1},
			Grid2D{1, 1},
			Grid2D{2, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{0, 1},
			Grid2D{0, 2}
	}
	};

	inline constexpr PieceRotations J{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{1, 0},
			Grid2D{-1, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{1, -1},
			Grid2D{0, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{1, 0},
			Grid2D{1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{0, 1},
			Grid2D{-1, 1}
	}
	};

	inline constexpr PieceRotations L{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{-1, 0},
			Grid2D{1, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, 1},
			Grid2D{0, -1},
			Grid2D{1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{-1, 0},
			Grid2D{-1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, 1},
			Grid2D{0, -1},
			Grid2D{-1, -1}
	}
	};

	inline constexpr PieceRotations O{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{1, -1},
			Grid2D{0, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{1, -1},
			Grid2D{0, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{1, -1},
			Grid2D{0, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{1, -1},
			Grid2D{0, -1}
	}
	};

	inline constexpr PieceRotations S{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{1, -1},
			Grid2D{-1, 0}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{1, 0},
			Grid2D{1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{1, 0},
			Grid2D{0, 1},
			Grid2D{-1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{-1, -1},
			Grid2D{0, 1}
	}
	};

	inline constexpr PieceRotations T{
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

	inline constexpr PieceRotations Z{
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, -1},
			Grid2D{-1, -1},
			Grid2D{1, 0}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{0, 1},
			Grid2D{1, 0},
			Grid2D{1, -1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{0, 1},
			Grid2D{1, 1}
	},
		PieceOffset{
			Grid2D{0, 0},
			Grid2D{-1, 0},
			Grid2D{-1, 1},
			Grid2D{0, -1}
	}
	};

	inline constexpr PieceRotations none{};

	inline constexpr Pieces Data
	{	
		I,
		J,
		L,
		O,
		S,
		T,
		Z,
		none,
	};

}

namespace input
{
	struct PieceActions
	{
		bool movLeft{};
		bool movRight{};

		bool holdLeft{};
		bool holdRight{};

		bool rotLeft{};
		bool rotRight{};
		bool rot180{};

		bool softDrop{};
		bool hardDrop{};
	};

	PieceActions getPieceAction();
}

namespace piece
{	
	using Board = std::array<
		std::array<cell::Cell, options::game::columns>,
		options::game::rows
	>;

	class Piece
	{
	public:
		struct HoldState
		{
			std::chrono::time_point<std::chrono::steady_clock> lastPress;
			std::chrono::time_point<std::chrono::steady_clock> lastMove;
		};

		Piece(grid::Grid2D spawnPos, PieceType type, int rotationState = 0);

		void updatePiece(const input::PieceActions& actions, std::chrono::time_point<std::chrono::steady_clock>& lastGravityTick, const Board& staticPieces);

		void drawPiece() const;

		PieceType type() const { return m_type; }

	private:
		bool isCollidingStaticPiece(const Board& staticPieces, grid::Grid2D testPos) const;
		bool isCollidingBottom(const Board& staticPieces) const;
		bool isCollidingSides(const Board& staticPieces, int moveOffset) const;

		HoldState m_leftState{};
		HoldState m_rightState{};

		std::chrono::time_point<std::chrono::steady_clock> m_lastCollision{};

		grid::Grid2D m_gridPos{0, 0};

		PieceType m_type{};
		int m_rotationState{0};

	};

	Piece getRandomPiece();

	void checkActivePieces(std::vector<Piece>& activePieces);

	Piece generateBag(std::vector<Piece>& currentBag);
}
