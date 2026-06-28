#pragma once

#include "Grid.hpp"
#include "Options.hpp"
#include "PieceType.hpp"
#include "Bag.hpp"
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

		Piece(grid::Grid2D spawnPos, pieceType::PieceType type, int rotationState = 0);

		void update(const input::PieceActions& actions, Board& staticPieces, bag::Bag& currentBag, bag::Bag& nextBag);
		void draw() const;
		pieceType::PieceType type() const { return m_type; }

		void drawGhostPiece(const Board& staticPieces) const;

		void reset(bag::Bag& currentBag, bag::Bag& nextBag);
		
		std::chrono::time_point<std::chrono::steady_clock> lastGravityTick() const { return m_lastGravityTick; } 
		std::chrono::time_point<std::chrono::steady_clock> lockStart() const { return m_lockStart; } 

		bool isCollidingBottom(const Board& staticPieces) const;

	private:
		bool isCollidingStaticPiece(const Board& staticPieces, grid::Grid2D testPos) const;
		bool isCollidingSides(const Board& staticPieces, int moveOffset) const;

		grid::Grid2D getHardDropPos(const Board& staticPieces) const;

		void setStaticData(Board& staticPieces) const;

		HoldState m_leftState{};
		HoldState m_rightState{};

		grid::Grid2D m_gridPos{0, 0};

		std::chrono::time_point<std::chrono::steady_clock> m_lastGravityTick{std::chrono::steady_clock::now()};

		std::chrono::time_point<std::chrono::steady_clock> m_lockStart{std::chrono::steady_clock::now()};
		int m_lockCount{0};

		pieceType::PieceType m_type{};
		int m_rotationState{0};

	};

	void drawStatic(const Board& staticPieces);

}
