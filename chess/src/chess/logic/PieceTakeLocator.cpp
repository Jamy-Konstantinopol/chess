#include "PieceTakeLocator.h"

#include "../pieces/logic/PieceFinder.h"
#include "../pieces/Pawn.h"

#include <memory>

Chess::Coordinate Chess::PieceTakeLocator::Find(std::shared_ptr<IPiece> piece, const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard, Coordinate to)
{
	auto pawnOnPassCoordinate = Coordinate(to.get_File(), piece->get_Position().get_Rank());
	auto finder = std::make_shared<PieceFinder>(piecesOnBoard);
	auto currentPawn = std::dynamic_pointer_cast<Pawn>(piece);
	auto opponentPawn = std::dynamic_pointer_cast<Pawn>(finder->Find(pawnOnPassCoordinate));
	auto carrentColor = piece->get_ColorAndType().get_Color();

	if (currentPawn && opponentPawn
		&& opponentPawn->get_CanEnPassant()
		&& opponentPawn->get_ColorAndType().get_Color() != currentPawn->get_ColorAndType().get_Color())
	{
		return pawnOnPassCoordinate;
	}
	else
	{
		return to;
	}
}
