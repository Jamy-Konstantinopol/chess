#pragma once

#include "ePieceColor.h"
#include "IPiece.h"
#include "PieceColorAndType.h"
#include "../Coordinate.h"

namespace Chess
{
	class King : public IPiece
	{
	private:
		PieceColorAndType m_colorAndType{};
		Coordinate m_position{};
		
	public:
		King(ePieceColor color);
		~King() {};

	public:
		PieceColorAndType get_ColorAndType() const override { return m_colorAndType; };
		Coordinate get_Position() const override { return m_position; }

	public:
		void Move(Coordinate to) override;
	};
}
