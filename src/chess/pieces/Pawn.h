#pragma once

#include "ePieceColor.h"
#include "IPiece.h"
#include "PieceColorAndType.h"
#include "../Coordinate.h"

#include <vector>

namespace Chess
{
	class Pawn : public IPiece
	{
	private:
		static constexpr int m_MAX_POSIBLE_COUNT_MOVES = 2;
	private:
		PieceColorAndType m_colorAndType{};
		Coordinate m_position{};

	public:
		Pawn(ePieceColor color, char file);
		~Pawn() {};

	public:
		PieceColorAndType get_ColorAndType() const override { return m_colorAndType; };
		Coordinate get_Position() const override { return m_position; }

	public:
		void Move(Coordinate to) override;
	};
}
