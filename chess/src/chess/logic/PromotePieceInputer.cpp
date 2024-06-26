#include "PromotePieceInputer.h"

#include "Sizes.h"
#include "../pieces/logic/PieceTypeConverter.h"

#include <conio.h>
#include <iostream>
#include <stdexcept>

Chess::ePieceType Chess::PromotePieceInputer::Input() const
{
	while (true)
	{
		m_signalEnter("PROMOTE\nYou can Choose: B K Q R\nEnter: ");

		std::string input;
		std::getline(std::cin, input);

		input[0] = std::toupper(input[0]);
		
		if (input[0] == PieceTypeConverter::ConvertToString(ePieceType::KING)[0])
		{
			input[0] = std::tolower(input[0]);
		}

		if (input[0] == PieceTypeConverter::ConvertToString(ePieceType::BISHOP)[0])
		{
			return ePieceType::BISHOP;
		}
		if (input[0] == PieceTypeConverter::ConvertToString(ePieceType::KNIGHT)[0])
		{
			return ePieceType::KNIGHT;
		}
		if (input[0] == PieceTypeConverter::ConvertToString(ePieceType::QUEEN)[0])
		{
			return ePieceType::QUEEN;
		}
		if (input[0] == PieceTypeConverter::ConvertToString(ePieceType::ROOK)[0])
		{
			return ePieceType::ROOK;
		}

		m_signalEnter("Piece is invalid\nPress any key to continue...\n");
		auto _ = _getch();
	}

	throw std::invalid_argument("Imposible to be here... How did you do that!?");
}
