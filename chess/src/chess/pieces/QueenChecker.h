#pragma once

#include "Queen.h"
#include "logic/IMoveChecker.h"
#include "../logic/Coordinate.h"

#include <vector>

namespace Chess
{
	class QueenChecker : public IMoveChecker
	{
	private:
		std::vector<Coordinate> FindPossibleMoves(const std::shared_ptr<Queen>& queen, const std::vector<std::shared_ptr<Piece>>& piecesOnBoard) const;

	public:
		std::vector<Coordinate> GetMoves(const std::shared_ptr<Piece>& piece, const std::vector<std::shared_ptr<Piece>>& piecesOnBoard) const override;
	};
}
