#include "PieceDirector.h"

#include "Coordinate.h"
#include "Counts.h"
#include "Sizes.h"
#include "PieceSignalDirector.h"
#include "PieceTakeLocator.h"
#include "Promotion.h"
#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/logic/CheckChecker.h"
#include "../pieces/logic/ePieceColor.h"
#include "../pieces/logic/PieceColorAndType.h"
#include "../pieces/logic/PieceFinder.h"
#include "../pieces/Pawn.h"
#include "../pieces/Piece.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "../LableDisplayer.h"

Chess::PieceDirector::PieceDirector(std::vector<std::shared_ptr<Piece>>& piecesOnBoard, const std::shared_ptr<PieceSignalDirector>& signalDirector)
	: m_piecesOnBoard(piecesOnBoard), m_signalDirector(signalDirector)
{
	m_eatenPieces.reserve(MAX_COUNT_ELEMENTS);
	m_promotion = std::make_shared<Promotion>();
}

const std::shared_ptr<Chess::Piece>& Chess::PieceDirector::get_CurrentPiece() const
{
	return m_currentPiece;
}

const std::vector<std::shared_ptr<Chess::Piece>>& Chess::PieceDirector::get_EatenPieces() const
{
	return m_eatenPieces;
}

bool Chess::PieceDirector::get_IsCheck() const
{
	return m_isCheck;
}

const std::vector<std::shared_ptr<Chess::Piece>>& Chess::PieceDirector::get_PiecesOnBoard() const
{
	return m_piecesOnBoard;
}

void Chess::PieceDirector::Take(int indexOnBoard)
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

std::shared_ptr<Chess::Piece> Chess::PieceDirector::GetPiece(const Coordinate& from) const
{
	for (std::shared_ptr<Chess::Piece> pieceOnBoard : m_piecesOnBoard)
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

void Chess::PieceDirector::MovePiece(const Coordinate& to, const boost::signals2::signal<void()>& signalChessboardUndated)
{
	auto fromTake = std::make_unique<PieceTakeLocator>()->Find(m_currentPiece, m_piecesOnBoard, to);

	auto it = std::find_if(m_piecesOnBoard.begin(), m_piecesOnBoard.end(), [fromTake](std::shared_ptr<Piece> current)
		{
			return current->get_Position() == fromTake;
		});

	if (it != m_piecesOnBoard.end())
	{
		Take(std::distance(m_piecesOnBoard.begin(), it));
	}

	m_currentPiece->Move(to);
	m_signalDirector->Invite();

	if (typeid(*m_currentPiece) == typeid(Pawn)
		&& (m_currentPiece->get_Position().get_Rank() == 1 && m_currentPiece->get_ColorAndType().get_Color() == ePieceColor::BLACK
			|| m_currentPiece->get_Position().get_Rank() == CHESSBOARD_SIZE && m_currentPiece->get_ColorAndType().get_Color() == ePieceColor::WHITE))
	{
		signalChessboardUndated();
		m_promotion->PromoteConditionally(std::static_pointer_cast<Pawn>(m_currentPiece), m_piecesOnBoard);
	}

	auto checkChecker = std::make_unique<CheckChecker>();

	ePieceColor color;

	if (m_currentPiece->get_ColorAndType().get_Color() == ePieceColor::BLACK)
	{
		color = ePieceColor::WHITE;
	}
	else if (m_currentPiece->get_ColorAndType().get_Color() == ePieceColor::WHITE)
	{
		color = ePieceColor::BLACK;
	}

	m_isCheck = checkChecker->IsCheck(color, m_piecesOnBoard);
	m_signalDirector->Invite(m_isCheck);
}
