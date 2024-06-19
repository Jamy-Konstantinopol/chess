#include "PieceDirector.h"

#include "Counts.h"
#include "Sizes.h"
#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/logic/ePieceColor.h"
#include "../pieces/logic/PieceColorAndType.h"
#include "../pieces/logic/PieceFinder.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"

Chess::PieceDirector::PieceDirector(std::vector<std::shared_ptr<IPiece>> piecesOnBoard, std::shared_ptr<PieceSignalDirector> signalDirector) : m_signalDirector(signalDirector), m_piecesOnBoard(piecesOnBoard)
{
	m_eatenPieces.reserve(MAX_COUNT_ELEMENTS);
}

const std::shared_ptr<Chess::IPiece>& Chess::PieceDirector::get_CurrentPiece() const
{
	return m_currentPiece;
}

const std::vector<std::shared_ptr<Chess::IPiece>>& Chess::PieceDirector::get_EatenPieces() const
{
	return m_eatenPieces;
}

const std::vector<std::shared_ptr<Chess::IPiece>>& Chess::PieceDirector::get_PiecesOnBoard() const
{
	return m_piecesOnBoard;
}

void Chess::PieceDirector::Take(size_t indexOnBoard)
{
	m_eatenPieces.emplace_back(std::move(m_piecesOnBoard[indexOnBoard]));
	m_piecesOnBoard.erase(m_piecesOnBoard.begin() + indexOnBoard);
}

Chess::PieceColorAndType Chess::PieceDirector::GetPieceColorAndType(const Coordinate& from) const
{
	auto piece = GetPiece(from);

	if (!piece)
	{
		return PieceColorAndType();
	}

	return piece->get_ColorAndType();
}

std::shared_ptr<Chess::IPiece> Chess::PieceDirector::GetPiece(const Coordinate& from) const
{
	for (std::shared_ptr<Chess::IPiece> pieceOnBoard : m_piecesOnBoard)
	{
		if (pieceOnBoard->get_Position() == from)
		{
			return pieceOnBoard;
		}
	}

	return nullptr;
}

void Chess::PieceDirector::InitCurrentPiece(const Coordinate& from)
{
	m_currentPiece = GetPiece(from);
}

void Chess::PieceDirector::MovePiece(const Coordinate& to)
{
	auto pawnOnPassCoordinate = Coordinate(to.get_File(), get_CurrentPiece()->get_Position().get_Rank());
	auto finder = std::make_shared<PieceFinder>(m_piecesOnBoard);
	auto currentPawn = std::dynamic_pointer_cast<Pawn>(get_CurrentPiece());
	auto opponentPawn = std::dynamic_pointer_cast<Pawn>(finder->Find(pawnOnPassCoordinate));
	auto carrentColor = m_currentPiece->get_ColorAndType().get_Color();

	auto takeIfCurrentPosition = [&](Coordinate takeFrom)
		{
			auto it = std::find_if(m_piecesOnBoard.begin(), m_piecesOnBoard.end(), [takeFrom](std::shared_ptr<IPiece> current)
				{
					return current->get_Position() == takeFrom;
				});

			if (it != m_piecesOnBoard.end())
			{
				Take(std::distance(m_piecesOnBoard.begin(), it));
			}
		};

	if (currentPawn && opponentPawn
		&& opponentPawn->get_CanEnPassant()
		&& opponentPawn->get_ColorAndType().get_Color() != currentPawn->get_ColorAndType().get_Color())
	{
		takeIfCurrentPosition(pawnOnPassCoordinate);
	}
	else
	{
		takeIfCurrentPosition(to);
	}

	m_currentPiece->Move(to);
	m_signalDirector->Invite();
}
