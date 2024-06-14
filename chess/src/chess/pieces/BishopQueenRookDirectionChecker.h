#pragma once

#include "IPiece.h"
#include "PieceFinder.h"
#include "../Coordinate.h"

#include <memory>
#include <vector>

namespace Chess
{
	class BishopQueenRookDirectionChecker
	{
	public:
		static std::vector<Coordinate> FindPossibleMoves(const std::shared_ptr<PieceFinder>& finder, const std::shared_ptr<IPiece>& current, std::pair <int, int> coordinateIncrement);
	};
}
