#pragma once

#include "ePieceColor.h"
#include "ePieceType.h"

namespace Chess
{
	struct PieceColorAndType
	{
		ePieceColor m_color;
		ePieceType m_type;

	public:
		PieceColorAndType();
		PieceColorAndType(ePieceColor color, ePieceType type);

	public:
		ePieceColor get_Color() const;
		ePieceType get_Type() const;

	public:
		PieceColorAndType& operator=(const PieceColorAndType& other);
		bool operator==(const PieceColorAndType& other) const;
	};
}
