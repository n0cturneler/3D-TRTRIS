#pragma once

#include "Grid.hpp"
#include "Options.hpp"

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
	using Pieces = std::array<PieceRotations, 7>;

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
			Grid2D{-1, -1}
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

	inline constexpr Pieces Data
	{
		I,
		J,
		L,
		O,
		S,
		T,
		Z
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



class Piece
{
public:

	struct HoldState
	{
		std::chrono::time_point<std::chrono::steady_clock> lastPress;
		std::chrono::time_point<std::chrono::steady_clock> lastMove;
	};

	enum class Type { I, J, L, O, S, T, Z };

	Piece(grid::Grid2D spawnPos, Type type, int rotationState = 0);

	void updatePiece(const input::PieceActions& actions, std::chrono::time_point<std::chrono::steady_clock>& lastGravityTick);
	void drawPiece() const;

	Type type() const { return m_type; }

private:
	grid::Grid2D m_gridPos{0, 0};

	Type m_type{};
	int m_rotationState{0};

	HoldState m_leftState{};
	HoldState m_rightState{};
};
