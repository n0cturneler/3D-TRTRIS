#pragma once

#include "Grid.hpp"
#include "Options.hpp"
#include "PieceType.hpp"
#include "Cell.hpp"
#include "Input.hpp"

#include <raylib.h>

#include <iostream> 
#include <vector>
#include <array>
#include <chrono>

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

		void update(const input::PieceActions& actions, Board& staticPieces);
		void draw() const;
		PieceType type() const { return m_type; }

		void reset();

		void drawGhostPiece(const Board& staticPieces) const;

	private:
		bool isCollidingStaticPiece(const Board& staticPieces, grid::Grid2D testPos) const;
		bool isCollidingBottom(const Board& staticPieces) const;
		bool isCollidingSides(const Board& staticPieces, int moveOffset) const;
		
		void setStaticData(Board& staticPieces) const;

		grid::Grid2D getHardDropPos(const Board& staticPieces) const;
		

		HoldState m_leftState{};
		HoldState m_rightState{};

		grid::Grid2D m_gridPos{0, 0};

		std::chrono::time_point<std::chrono::steady_clock> m_lastGravityTick{std::chrono::steady_clock::now()};

		std::chrono::time_point<std::chrono::steady_clock> m_lockStart{std::chrono::steady_clock::now()};
		int m_lockCount{0};

		PieceType m_type{};
		int m_rotationState{0};

	};

	PieceType getNextType();

	void drawStatic(const Board& staticPieces);
}
