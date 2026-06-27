#include "Pieces.hpp"

#include "Grid.hpp"
#include "PieceType.hpp"
#include "PieceOffsets.hpp"
#include "Options.hpp"
using namespace options;

#include "Cell.hpp"
using Board = std::array<
	std::array<cell::Cell, options::game::columns>,
	options::game::rows
>;

#include "Random.hpp"

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <vector>
#include <array>

piece::Piece::Piece(grid::Grid2D spawnPos, PieceType type, int rotationState)
	: m_gridPos{spawnPos}, m_type{type}, m_rotationState{rotationState}
{
}

void piece::Piece::update(const input::PieceActions& actions, Board& staticPieces)
{
	using ms = std::chrono::milliseconds;
	auto now{std::chrono::steady_clock::now()};

	if (actions.movLeft)
	{
		m_leftState.lastPress = now;
		
		if (not isCollidingSides(staticPieces, -1))
		{	
			m_lockStart = now;
			m_gridPos.x -= 1;
		}
	}
	if (actions.movRight)
	{
		m_rightState.lastPress = now;

		if (not isCollidingSides(staticPieces, 1))
		{	
			m_lockStart = now;
			m_gridPos.x += 1;
		}
	}

	if (actions.holdLeft)
	{
		auto duration_l = std::chrono::duration_cast<ms>(now - m_leftState.lastPress);
		auto duration_arr = std::chrono::duration_cast<ms>(now - m_leftState.lastMove);

		if (duration_l.count() >= game::DAS && duration_arr.count() >= game::ARR)
		{
			m_leftState.lastMove = now;
			if (not isCollidingSides(staticPieces, -1))
			{
				m_lockStart = now;
				m_gridPos.x -= 1;
			}
		}
	}
	if (actions.holdRight)
	{
		auto duration_r = std::chrono::duration_cast<ms>(now - m_rightState.lastPress);
		auto duration_arr = std::chrono::duration_cast<ms>(now - m_rightState.lastMove);

		if (duration_r.count() >= game::DAS && duration_arr.count() >= game::ARR)
		{
			m_rightState.lastMove = now;
			if (not isCollidingSides(staticPieces, 1))
			{
				m_lockStart = now;
				m_gridPos.x += 1;
			}
		}
	}

	if (actions.rotLeft) 
	{
		m_rotationState -= 1;
		m_lockStart = now;
	}
	if (actions.rotRight)
	{
		m_rotationState += 1;
		m_lockStart = now;
	}
	if (actions.rot180) 
	{
		m_rotationState += 2;
		m_lockStart = now;
	}

	m_rotationState = (m_rotationState + 4) % 4;

	int currentDropRate{game::gravityMS};
	if (actions.softDrop) { currentDropRate = game::softdropMS; }

	auto duration_grav = std::chrono::duration_cast<ms>(now - m_lastGravityTick);
	if (duration_grav.count() >= currentDropRate)
	{
		if (not isCollidingBottom(staticPieces))
		{
			m_lastGravityTick = now;
			m_lockStart = now;
			m_gridPos.y += 1;
		}
	}

	if (actions.hardDrop)
	{
		m_lastGravityTick = now;
		m_gridPos = getHardDropPos(staticPieces);
		setStaticData(staticPieces);
		reset();
	}

	auto duration_lock = std::chrono::duration_cast<ms>(now - m_lockStart);
	if (isCollidingBottom(staticPieces))
	{	
		if (duration_lock.count() >= game::lockDelayMS)
		{
			m_lockStart = now;
			setStaticData(staticPieces);
			reset();
		}
	}
}

void piece::Piece::draw() const
{
	assert(m_type != PieceType::none);
	assert(static_cast<int>(m_type) <= 6);
	assert(m_rotationState >= 0 && m_rotationState <= 3);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};

	for (const grid::Grid2D& offset : data)
	{
		grid::Grid2D gridPosition = grid::add(m_gridPos, offset);
		Vector3 position = grid::gridToWorld(gridPosition);

		Color mainColor{colors::piece[pieceIndex]};
		Color borderColor{colors::pieceBorder[pieceIndex]};

		if (gridPosition.x < 0 ||
			gridPosition.y < 0 || 
			gridPosition.x > game::columns - 1 || 
			gridPosition.y > game::rows - 1)
		{
			mainColor = Fade(mainColor, 0.15f);
			borderColor = Fade(borderColor, 1.0f);
		}

		DrawCube(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, mainColor);
		DrawCubeWires(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, borderColor);
	}
}

void piece::Piece::reset()
{
	m_gridPos = game::gridSpawn;
	m_rotationState = 0;
	m_type = {getNextType()};
}

bool piece::Piece::isCollidingStaticPiece(const Board& staticPieces, grid::Grid2D testPos) const
{
	if (testPos.x >= 0 &&
		testPos.x < game::columns &&
		testPos.y >= 0 &&
		testPos.y < game::rows)
	{
		if (staticPieces[static_cast<std::size_t>(testPos.y)][static_cast<std::size_t>(testPos.x)].type != PieceType::none)
		{
			return true;
		}
	}
	return false;
}

bool piece::Piece::isCollidingSides(const Board& staticPieces, int moveOffset) const
{
	assert(m_type != PieceType::none);
	assert(static_cast<int>(m_type) <= 6);
	assert(m_rotationState >= 0 && m_rotationState <= 3);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};

	for (const grid::Grid2D& offset : data)
	{
		grid::Grid2D testPos{grid::add(offset, m_gridPos)};

		testPos.x += moveOffset;

		if (isCollidingStaticPiece(staticPieces, testPos))
		{
			return true;
		}

		if ((testPos.x < 0) || (testPos.x >= game::columns))
		{
			return true;
		}
	}

	return false;
}

bool piece::Piece::isCollidingBottom(const Board& staticPieces) const
{
	assert(m_type != PieceType::none);
	assert(static_cast<int>(m_type) <= 6);
	assert(m_rotationState >= 0 && m_rotationState <= 3);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};

	int maxY{game::rows - 1};

	for (const grid::Grid2D& offset : data)
	{
		grid::Grid2D testPos{grid::add(offset, m_gridPos)};
		testPos.y += 1;

		if (isCollidingStaticPiece(staticPieces, testPos))
		{
			return true;
		}
		
		if (testPos.y > maxY)
		{
			return true;
		}
	}

	return false;
}

void piece::Piece::setStaticData(Board& staticPieces) const
{
	assert(m_type != PieceType::none);
	assert(static_cast<int>(m_type) <= 6);
	assert(m_rotationState >= 0 && m_rotationState <= 3);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};

	for (const grid::Grid2D& offset : data)
	{	
		grid::Grid2D testPos{grid::add(offset, m_gridPos)};

		if (testPos.x >= 0 &&
			testPos.x < game::columns &&
			testPos.y >= 0 &&
			testPos.y < game::rows)
		{
			if (staticPieces[static_cast<std::size_t>(testPos.y)][static_cast<std::size_t>(testPos.x)].type == PieceType::none)
			{
				staticPieces[static_cast<std::size_t>(testPos.y)][static_cast<std::size_t>(testPos.x)].type = m_type;
			}
		}
	}
}

grid::Grid2D piece::Piece::getHardDropPos(const Board& staticPieces)
{	
	assert(m_type != PieceType::none);
	assert(static_cast<int>(m_type) <= 6);
	assert(m_rotationState >= 0 && m_rotationState <= 3);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};

	int maxY{game::rows - 1};

	for (int y{0}; y <= (maxY - m_gridPos.y); ++y)
	{	
		for (const grid::Grid2D& offset : data)
		{
			grid::Grid2D testPos{grid::add(offset, m_gridPos)};
			testPos.y += y;

			if (isCollidingStaticPiece(staticPieces, testPos))
			{	
				return {m_gridPos.x, m_gridPos.y + y - 1};
			}
			
			if (testPos.y >= maxY)
			{	
				return {m_gridPos.x, m_gridPos.y + y};
			}
			
		}
	}
	return m_gridPos;
}

void piece::drawStatic(const Board& staticPieces)
{
	for (int y{0}; y < game::rows; ++y)
	{	
		for (int x{0}; x < game::columns; ++x)
		{
			if (staticPieces[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].type != PieceType::none)
			{	
				auto pieceIndex{static_cast<std::size_t>(staticPieces[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].type)};

				Color mainColor{colors::piece[pieceIndex]};
				Color borderColor{colors::pieceBorder[pieceIndex]};

				Vector3 position = grid::gridToWorld({x, y});

				DrawCube(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, mainColor);
				DrawCubeWires(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, borderColor);
			}
		}
	}
}

PieceType piece::getNextType()
{
	int pieceIndex{Random::get(0, 6)};
	return static_cast<PieceType>(pieceIndex);
}

input::PieceActions input::getPieceAction()
{
	input::PieceActions actions{};

	if (IsKeyPressed(KEY_LEFT)) actions.movLeft = true;
	if (IsKeyPressed(KEY_RIGHT)) actions.movRight = true;

	if (IsKeyDown(KEY_LEFT)) actions.holdLeft = true;
	if (IsKeyDown(KEY_RIGHT)) actions.holdRight = true;

	if (IsKeyPressed(KEY_SPACE)) actions.hardDrop = true;
	if (IsKeyDown(KEY_DOWN)) actions.softDrop = true;

	if (IsKeyPressed(KEY_Z)) actions.rotLeft = true;
	if (IsKeyPressed(KEY_X)) actions.rotRight = true;

	if (IsKeyPressed(KEY_C)) actions.rot180 = true;

	return actions;
}
