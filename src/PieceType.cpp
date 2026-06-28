#include "PieceType.hpp"

#include <string_view>

const char* pieceType::pieceTypeToString(PieceType type)
{
	switch (type)
	{
	case pieceType::PieceType::I: return "I";
	case pieceType::PieceType::J: return "J";
	case pieceType::PieceType::L: return "L";
	case pieceType::PieceType::O: return "O";
	case pieceType::PieceType::S: return "S";
	case pieceType::PieceType::T: return "T";
	case pieceType::PieceType::Z: return "Z";
	case pieceType::PieceType::none: return "X";

	default:
		break;
	}

}
