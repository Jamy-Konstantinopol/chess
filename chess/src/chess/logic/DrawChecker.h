#pragma once

#include <map>
#include <memory>
#include <string>

namespace Chess
{
	class Chessboard;

	class DrawChecker
	{
	private:
		int m_movesCountWithoutPawnAndTaking = 0;
		size_t m_lastCountEatenPeaces = 0;

	private:
		void CalculateMovesCountWithoutPawnAndTaking(const std::shared_ptr<Chessboard>& chessboard);
		bool IsInsufficientMaterial(const std::shared_ptr<Chessboard>& chessboard);

	public:
		bool IsDraw(const std::shared_ptr<Chessboard>& chessboard);
	};
}
