#include "Pawn.h"

#include "../logic/eError.h"
#include "../logic/ErrorConverter.h"
#include "../logic/Sizes.h"

#include <stdexcept>

Chess::Pawn::Pawn(ePieceColor color, char file)
{
	if (file < 'A' || file > 'A' + CHESSBOARD_SIZE - 1)
	{
		throw std::out_of_range(ErrorConverter::ToString(Chess::eError::OUT_OF_CHESSBOARD));
	}

	m_colorAndType = PieceColorAndType(color, ePieceType::PAWN);

	switch (color)
	{
	case Chess::ePieceColor::BLACK:
		m_position = Coordinate(file, CHESSBOARD_SIZE - 1);
		break;
	case Chess::ePieceColor::WHITE:
		m_position = Coordinate(file, 2);
		break;
	default:
		throw std::out_of_range(ErrorConverter::ToString(Chess::eError::OUT_OF_CHESSBOARD));
	}
}

Chess::Pawn::Pawn(ePieceColor color, char file, const std::shared_ptr<PieceSignalDirector>& signalDirector) : Pawn(color, file)
{
	MakeTracking(signalDirector);
}

Chess::Pawn::Pawn(ePieceColor color, Coordinate coordinate)
	: Piece(PieceColorAndType(color, ePieceType::PAWN), coordinate) { }

Chess::Pawn::Pawn(ePieceColor color, Coordinate coordinate, const std::shared_ptr<PieceSignalDirector>& signalDirector) : Pawn(color, coordinate)
{
	MakeTracking(signalDirector);
}

bool Chess::Pawn::get_CanEnPassant() const
{
	return m_canEnPassant;
}

bool Chess::Pawn::get_IsNotMoved() const
{
	return m_isNotMoved;
}

void Chess::Pawn::LostEnPassant()
{
	m_canEnPassant = false;
}

void Chess::Pawn::MakeTracking(const std::shared_ptr<Chess::PieceSignalDirector>& signalDirector)
{
	if (!signalDirector)
	{
		return;
	}

	signalDirector->ConnectMove([this]()
		{
			if (!m_isOnPawnFirstMove)
			{
				LostEnPassant();
			}

			m_isOnPawnFirstMove = false;
		});
}

void Chess::Pawn::Move(Coordinate to, bool isRealMove)
{
	if(isRealMove)
	{
		if (abs(to.get_Rank() - get_Position().get_Rank()) == 2)
		{
			m_canEnPassant = m_isNotMoved;
		}
		else
		{
			LostEnPassant();
		}

		m_isOnPawnFirstMove = m_isNotMoved;
		m_isNotMoved = false;
	}

	Piece::Move(to);
}
