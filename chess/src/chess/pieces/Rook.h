#pragma once

#include "logic/ePieceColor.h"
#include "IPiece.h"
#include "King.h"
#include "logic/eCastleSide.h"
#include "logic/ICastlable.h"
#include "logic/IKing.h"
#include "logic/PieceColorAndType.h"
#include "../logic/Coordinate.h"
#include <stdio.h>

#include <boost/signals2.hpp>

namespace Chess
{
	class Rook : public IPiece, public ICastable
	{
	private:
		bool m_canMakeCastling = false;
		boost::signals2::connection m_castlingConnection;
		PieceColorAndType m_colorAndType{};
		Coordinate m_position{};

	public:
		Rook(ePieceColor pieceColor, int orderNumber);
		Rook(ePieceColor pieceColor, int orderNumber, std::shared_ptr<King> king);

	public:
		bool get_CanMakeCastling() const override;
		PieceColorAndType get_ColorAndType() const override;
		Coordinate get_Position() const override;

	private:
		void DisableCastling();

	public:
		void Move(Coordinate to) override;
		void OnCastling(Coordinate to, eCastleSide side) override;
	};
}
