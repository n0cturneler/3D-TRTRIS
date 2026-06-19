#include "Pieces.hpp"

#include "Grid.hpp"
#include "Options.hpp"
using namespace options;

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <print>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <cassert>

Piece::Piece(grid::Grid2D spawnPos, Type type, int rotationState)
	: m_gridPos{spawnPos}, m_type{type}, m_rotationState{rotationState}
{
}

void Piece::updatePiece(const input::PieceActions& actions, std::chrono::time_point<std::chrono::steady_clock>& lastGravityTick)
{	 
	using ms = std::chrono::milliseconds;
	auto now{std::chrono::steady_clock::now()};

	if (actions.movLeft)
	{	
		m_leftState.lastPress = now;
		m_gridPos.x -= 1;
	}
	if (actions.movRight)
	{
		m_rightState.lastPress = now;
		m_gridPos.x += 1;
	}

	if (actions.holdLeft)
	{	
		auto duration_l = std::chrono::duration_cast<ms>(now - m_leftState.lastPress);
		auto duration_arr = std::chrono::duration_cast<ms>(now - m_leftState.lastMove);

		if (duration_l.count() >= game::DAS && duration_arr.count() >= game::ARR)
		{	
			m_leftState.lastMove = now;
			m_gridPos.x -= 1;
		}
	}
	if (actions.holdRight)
	{
		auto duration_r = std::chrono::duration_cast<ms>(now - m_rightState.lastPress);
		auto duration_arr = std::chrono::duration_cast<ms>(now - m_rightState.lastMove);

		if (duration_r.count() >= game::DAS && duration_arr.count() >= game::ARR)
		{	
			m_rightState.lastMove = now;
			m_gridPos.x += 1;
		}
	}
	
	if (actions.rotLeft) m_rotationState += 1;
	if (actions.rotRight) m_rotationState -= 1;
	if (actions.rot180) m_rotationState += 2;

	m_rotationState = (m_rotationState + 4) % 4;

	auto duration_g = std::chrono::duration_cast<ms>(now - lastGravityTick);
	if (duration_g.count() >= game::gravityMS)
	{
		lastGravityTick = now;
		m_gridPos.y += 1;
	}
}

void Piece::drawPiece() const
{
	assert(static_cast<int>(m_type) < 7);
	assert(m_rotationState >= 0 && m_rotationState < 4);

	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& data{pieceData::Data[pieceIndex][rotationState]};	

	for (const grid::Grid2D& offset : data)
	{	
		grid::Grid2D gridPosition = grid::add(m_gridPos, offset);
		Vector3 position = grid::gridToWorld(gridPosition);

		Color mainColor{colors::piece[pieceIndex]};
		Color borderColor{colors::pieceBorder[pieceIndex]};

		if (gridPosition.x < 0 || gridPosition.y < 0 || gridPosition.x > game::columns - 1 || gridPosition.y > game::rows - 1)
		{
			mainColor = Fade(mainColor, 0.15f);
			borderColor = Fade(borderColor, 1.0f);
		}

		DrawCube(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, mainColor);
		DrawCubeWires(position, game::cubeSize.x, game::cubeSize.y, game::cubeSize.z, borderColor);
	}

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
