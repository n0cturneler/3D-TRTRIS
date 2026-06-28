#pragma once

#include "Pieces.hpp"
#include "Bag.hpp"

#include <raylib.h>

#include <imgui.h>

#include <chrono>
#include <string_view>

namespace UI
{	
	inline ImFont* mainFont = nullptr;
	inline ImFont* altFontBig = nullptr;
	inline ImFont* tetrisFontMedium = nullptr;

	void initialize();

	void FPS();
	void lockDelay(const piece::Piece& activePiece, const piece::Board& staticPieces);
	void drawBag(bag::Bag& currentBag, bag::Bag& nextBag);

	const char* textToTetrisFont(const char* text);

}
