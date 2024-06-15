#include "KnightChecker.h"

#include "../logic/Counts.h"
#include "../logic/eError.h"
#include "../logic/ErrorConverter.h"
#include "../logic/Sizes.h"

#include <memory>
#include <stdexcept>

std::vector<Chess::Coordinate> Chess::KnightChecker::FindPossibleMoves(const std::shared_ptr<Knight>& knight, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard)
{
	if (knight->get_Position().get_File() < 'A'
		|| knight->get_Position().get_File() >= 'A' + CHESSBOARD_SIZE
		|| knight->get_Position().get_Rank() < 1
		|| knight->get_Position().get_Rank() > CHESSBOARD_SIZE)
	{
		throw std::out_of_range(ErrorConverter::ToString(Chess::eError::OUT_OF_CHESSBOARD));
	}

	std::vector<Coordinate> moves;
	moves.reserve(COUNT_OF_KNIGHT_WAYS);

	auto currentPos = knight->get_Position();

	for (const auto& move : m_knightMoveDirections)
	{
		auto newFile = currentPos.get_File() + move.first;
		auto newRank = currentPos.get_Rank() + move.second;

		if (newFile < 'A' || newFile >= 'A' + CHESSBOARD_SIZE || newRank < 1 || newRank > CHESSBOARD_SIZE)
		{
			continue;
		}

		auto isBlocked = false;

		for (const auto& piece : piecesOnBoard)
		{
			if (piece->get_Position() == Coordinate(newFile, newRank)
				&& piece->get_ColorAndType().get_Color() == knight->get_ColorAndType().get_Color())
			{
				isBlocked = true;
				break;
			}
		}

		if (!isBlocked)
		{
			moves.emplace_back(newFile, newRank);
		}
	}

	return moves;
}

std::vector<Chess::Coordinate> Chess::KnightChecker::GetPossibleMoves(const std::shared_ptr<IPiece>& piece, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard)
{
	if (!piece || typeid(*piece) != typeid(Knight) || piece->get_ColorAndType().get_Type() != ePieceType::KNIGHT)
	{
		throw std::out_of_range(ErrorConverter::ToString(eError::NOT_CORRECT_PIECE));
	}

	return FindPossibleMoves(std::static_pointer_cast<Knight>(piece), piecesOnBoard);
}
