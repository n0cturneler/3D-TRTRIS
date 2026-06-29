#pragma once

#include <string_view>

namespace pieceType
{
	enum class PieceType
	{
		I,
		J,
		L,
		O,
		S,
		T,
		Z,
		none
	};

	std::string_view pieceTypeToString(PieceType type);
}

