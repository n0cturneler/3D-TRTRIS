#pragma once

#include <raylib.h>

#include "Options.hpp"

#include <iostream> 
#include <vector>
#include <array>

namespace PiecePos
{
	using PieceOffset = std::array<Vector3, 4>;
	using PieceRotations = std::array<PieceOffset, 4>;

	constexpr Vector3 cubeSize{Options::Game::cubeSize};

	inline const PieceRotations T_Piece{
		PieceOffset{
			Vector3{0.0f, 0.0f, 0.0f},
			Vector3{cubeSize.x, 0.0f, 0.0f},
			Vector3{-cubeSize.x, 0.0f, 0.0f},
			Vector3{0.0f, 0.0f, cubeSize.z}
	},
		PieceOffset{
			Vector3{0.0f, 0.0f, 0.0f},
			Vector3{cubeSize.x, 0.0f, 0.0f},
			Vector3{0.0f, 0.0f, cubeSize.z},
			Vector3{0.0f, 0.0f, -cubeSize.z}
	},
		PieceOffset{
			Vector3{0.0f, 0.0f, 0.0f},
			Vector3{cubeSize.x, 0.0f, 0.0f},
			Vector3{-cubeSize.x, 0.0f, 0.0f},
			Vector3{0.0f, 0.0f, -cubeSize.z}
	},
		PieceOffset{
			Vector3{0.0f, 0.0f, 0.0f},
			Vector3{-cubeSize.x, 0.0f, 0.0f},
			Vector3{0.0f, 0.0f, cubeSize.z},
			Vector3{0.0f, 0.0f, -cubeSize.z}
	},
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
	enum class Type { I, O, Z, S, T, J, L };

	Piece(Vector3 spawnPos, Type type, int rotationState = 0);

	void updatePiece(const Input::Actions& actions);
	void drawPiece();

private:
	Vector3 m_pos{0.0f, 0.0f, 0.0f};
	Type m_type{};
	int m_rotationState{};
};
