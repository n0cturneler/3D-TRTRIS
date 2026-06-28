#include "Input.hpp"

#include <raylib.h>

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
