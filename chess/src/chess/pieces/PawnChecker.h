#pragma once

#include "logic/IMoveChecker.h"
#include "IPiece.h"
#include "Pawn.h"
#include "logic/PieceFinder.h"

#include <map>
#include <memory>
#include <vector>

namespace Chess
{
	class PawnChecker :	public IMoveChecker
	{
	private:
		std::vector<Coordinate> GetForwardMoves(const std::shared_ptr<Pawn>& pawn, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard, const std::shared_ptr<PieceFinder>& finder) const;
		std::vector<Coordinate> GetDiagonalMoves(const std::shared_ptr<Pawn>& pawn, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard, const std::shared_ptr<PieceFinder>& finder) const;
		void ValidatePawn(const std::shared_ptr<Pawn>& pawn) const;

	public:
		std::vector<Coordinate> GetMoves(const std::shared_ptr<IPiece>& piece, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard) const override;
	};
}
