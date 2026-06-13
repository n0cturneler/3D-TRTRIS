#include "Pieces.hpp"

#include <raylib.h>

#include <iostream>
#include <vector>

Piece::Piece(Vector3 spawnPos, Type type, int rotationState) 
	: m_pos{spawnPos}, m_type{type}, m_rotationState{rotationState}
{

}

void Piece::updatePiece(const Input::Actions& actions)
{

}

void Piece::drawPiece()
{

}

Input::Actions getAction()
{

}
