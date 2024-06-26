#pragma once

#include "../IPiece.h"
#include "../../logic/Coordinate.h"

#include <memory>
#include <vector>

namespace Chess
{
	class IMoveChecker
	{
	public:
		virtual ~IMoveChecker() = default;

	public:
		virtual std::vector<Coordinate> GetMoves(const std::shared_ptr<IPiece>& piece, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard) const = 0;
	};
}
