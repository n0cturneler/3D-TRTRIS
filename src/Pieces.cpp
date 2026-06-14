#include "Pieces.hpp"

#include "Grid.hpp"
#include "Options.hpp"
using namespace Options;

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <print>
#include <cmath>
#include <cstdint>
#include <algorithm>

Piece::Piece(Grid::Grid2D spawnPos, Type type, int rotationState)
	: m_gridPos{spawnPos}, m_type{type}, m_rotationState{rotationState}
{
}

void Piece::updatePiece(const Input::Actions& actions, const std::uint64_t& currentCycle)
{
	if (actions.movLeft)
	{
		m_gridPos.x -= 1;
	}
	if (actions.movRight)
	{
		m_gridPos.x += 1;
	}

	if (actions.rotLeft)
	{
		m_rotationState += 1;
	}
	if (actions.rotRight)
	{
		m_rotationState -= 1;
	}
	if (actions.rot180)
	{
		m_rotationState += 2;
	}
	m_rotationState = (m_rotationState + 4) % 4;

	if (currentCycle % Game::rate == 0)
	{
		m_gridPos.y += 1;
	}

}

void Piece::drawPiece() const
{
	auto pieceIndex{static_cast<std::size_t>(m_type)};
	auto rotationState{static_cast<std::size_t>(m_rotationState)};
	const auto& pieceData{PieceData::Data[pieceIndex][rotationState]};

	for (const Grid::Grid2D& offset : pieceData)
	{	
		Vector3 position = Grid::gridToWorld(Grid::add(m_gridPos, offset));

		DrawCube(position, Game::cubeSize.x, Game::cubeSize.y, Game::cubeSize.z, Colors::pieceColors[pieceIndex]);
		DrawCubeWires(position, Game::cubeSize.x, Game::cubeSize.y, Game::cubeSize.z, Colors::pieceBorderColors[pieceIndex]);
	}
}

Input::Actions Input::getAction()
{
	Input::Actions actions{};

	//Das and arr later
	if (IsKeyPressed(KEY_LEFT)) actions.movLeft = true;
	if (IsKeyPressed(KEY_RIGHT)) actions.movRight = true;

	if (IsKeyPressed(KEY_SPACE)) actions.hardDrop = true;
	if (IsKeyDown(KEY_DOWN)) actions.softDrop = true;

	if (IsKeyPressed(KEY_Z)) actions.rotLeft = true;
	if (IsKeyPressed(KEY_X)) actions.rotRight = true;

	if (IsKeyPressed(KEY_C)) actions.rot180 = true;

	return actions;
}
