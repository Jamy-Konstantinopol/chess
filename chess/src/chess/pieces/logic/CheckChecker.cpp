#include "CheckChecker.h"

#include "MoveChecker.h"
#include "MoveCheckerFactory.h"
#include "PieceColorAndType.h"
#include "PieceFinder.h"
#include "../Piece.h"
#include "../King.h"
#include "../../logic/Coordinate.h"

bool Chess::CheckChecker::IsCheck(std::shared_ptr<King> king, const std::vector<std::shared_ptr<Piece>>& piecesOnBoard)
{
	for (const auto& piece : piecesOnBoard)
	{
		if (piece->GetColorAndType().GetColor() == king->GetColorAndType().GetColor())
		{
			continue;
		}
		
		auto moveChecker = std::make_unique<MoveCheckerFactory>()->Create(piece);
		auto moves = moveChecker->GetMoves(piece, piecesOnBoard);

		for (const auto& move : moves)
		{
			if (move == king->GetPosition())
			{
				return true;
			}
		}
	}

	return false;
}

bool Chess::CheckChecker::IsCheck(const Chess::ePieceColor& kingColor, const std::vector<std::shared_ptr<Piece>>& piecesOnBoard)
{
	for (const auto& piece : piecesOnBoard)
	{
		auto king = std::dynamic_pointer_cast<King>(piece);

		if (king && king->GetColorAndType().GetColor() == kingColor)
		{
			return IsCheck(king, piecesOnBoard);
		}
	}

	return false;
}
