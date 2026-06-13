#include "Pieces.hpp"

#include "Options.hpp"
using namespace Options;

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <print>
#include <cmath>
#include <cstdint>

Piece::Piece(Vector3 spawnPos, Type type, int rotationState)
	: m_pos{spawnPos}, m_type{type}, m_rotationState{rotationState}
{

}

void Piece::updatePiece(const Input::Actions& actions, const std::uint64_t& currentCycle)
{
	if ((currentCycle % Game::ARR) == 0)
	{
		if (actions.movLeft)
		{
			m_pos = Vector3Add(m_pos, {-Game::cubeSize.x, 0.0f, 0.0f});
		}
		if (actions.movRight)
		{
			m_pos = Vector3Add(m_pos, {Game::cubeSize.x, 0.0f, 0.0f});
		}
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

}

void Piece::drawPiece() const
{
	int pieceIndex{static_cast<int>(m_type)};
	const auto& pieceData{PieceData::Data[pieceIndex][m_rotationState]};

	for (const Vector3& offset : pieceData)
	{
		Vector3 position = Vector3Add(m_pos, offset);
		DrawCube(position, Game::cubeSize.x, Game::cubeSize.y, Game::cubeSize.z, Colors::pieceColors[pieceIndex]);
		DrawCubeWires(position, Game::cubeSize.x, Game::cubeSize.y, Game::cubeSize.z, Colors::pieceBorderColors[pieceIndex]);
	}
}

Input::Actions Input::getAction()
{
	Input::Actions actions{};

	if (IsKeyDown(KEY_LEFT)) actions.movLeft = true;
	if (IsKeyDown(KEY_RIGHT)) actions.movRight = true;

	if (IsKeyPressed(KEY_SPACE)) actions.hardDrop = true;
	if (IsKeyDown(KEY_DOWN)) actions.softDrop = true;

	if (IsKeyPressed(KEY_Z)) actions.rotLeft = true;
	if (IsKeyPressed(KEY_X)) actions.rotRight = true;

	if (IsKeyPressed(KEY_C)) actions.rot180 = true;

	return actions;
}
