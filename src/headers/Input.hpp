#pragma once

namespace input
{
	struct PieceActions
	{
		bool movLeft{};
		bool movRight{};

		bool holdLeft{};
		bool holdRight{};

		bool rotLeft{};
		bool rotRight{};
		bool rot180{};

		bool softDrop{};
		bool hardDrop{};

		bool holdPress{};
	};

	PieceActions getPieceAction();
}
