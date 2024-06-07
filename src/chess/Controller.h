#pragma once

#include "Chessboard.h"
#include "Coordinate.h"

#include <memory>

namespace Chess
{
	class Controller
	{
	private:
		std::shared_ptr<Chessboard> m_chessboard;

	public:
		Controller(std::shared_ptr<Chessboard> chessboard);

	public:
		bool TryMovePiece(Coordinate from, Coordinate to);
	};
}
