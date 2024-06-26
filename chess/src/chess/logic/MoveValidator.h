#pragma once

#include "Coordinate.h"
#include "../pieces/IPiece.h"
#include "../pieces/logic/CheckChecker.h"
#include "../pieces/logic/MoveChecker.h"
#include "../Player.h"

#include <memory>
#include <vector>

namespace Chess
{
	class MoveValidator
	{
	private:
		std::vector<std::shared_ptr<IPiece>> m_piecesCanMove;
		std::vector<Coordinate> m_possibleMoves;
		const std::vector<std::shared_ptr<IPiece>>& m_piecesOnBoard;
		const std::shared_ptr<Player> m_player;

	public:
		MoveValidator(const std::vector<std::shared_ptr<IPiece>>& piecesOnBoard, const std::shared_ptr<Player>& player);

	public:
		std::vector<Coordinate> get_PossibleMoves();

	public:
		void CalculatePiecesCanMove();
		void CalculatePossibleMoves(const std::shared_ptr<IPiece>& piece);
		void ClearPossibleMoves();
		void ClearPiecesCanMove();
		int GetPiecesCanMoveCount();
		bool IsCoordinateInPieceCanMove(Coordinate coordinate) const;
		bool IsCoordinateInPossibleMoves(Coordinate coordinate) const;
		bool IsValidMove(const std::shared_ptr<IPiece> piece, Coordinate to) const;
	};
}
