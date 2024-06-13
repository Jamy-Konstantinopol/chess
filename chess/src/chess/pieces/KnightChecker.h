#pragma once

#include "IMoveChecker.h"
#include "IPiece.h"
#include "Knight.h"
#include "../Coordinate.h"

#include <memory>
#include <vector>

namespace Chess
{
	class KnightChecker : public IMoveChecker
	{
	private:
		const std::vector<std::pair<int, int>> m_knightMoveDirections =
		{
			{ 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 },
			{ 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }
		};

	private:
		std::vector<Coordinate> FindPossibleMoves(const std::shared_ptr<Knight>& knight, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard);

	public:
		std::vector<Coordinate> GetPossibleMoves(const std::shared_ptr<IPiece>& piece, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard);
	};
}