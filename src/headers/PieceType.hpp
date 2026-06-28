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

	const char* pieceTypeToString(PieceType type);
}

