#pragma once

#include "ChessboardDisplayer.h"
#include "HandlerInputer.h"
#include "LableDisplayer.h"

#include <memory>
#include <variant>

namespace Chess
{
	class Chessboard;
	class Controller;

	class Game
	{
	private:
		std::unique_ptr<ChessboardDisplayer> m_chessboardDisplayer;
		std::shared_ptr<Chessboard> m_chessboard;
		std::shared_ptr<Controller> m_controller;
		std::shared_ptr<HandlerInputer> m_handlerInputer;
		std::unique_ptr<LableDisplayer> m_inputDisplayer;

	public:
		Game();
	
	private:
		bool ContinueGame() const;
		void HandleInput(std::function<Coordinate()> inputFunction, std::function<bool(const Coordinate&)> initFunction) const;

	public:
		void Play() const;
	};
}
