#pragma once
	
#include "Grid.hpp"

#include <array>

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
