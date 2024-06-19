#pragma once

#include "PieceSignalDirector.h"
#include "../pieces/IPiece.h"

#include <memory>
#include <vector>

namespace Chess
{
	class PieceInitializer
	{
	public:
		std::vector<std::shared_ptr<IPiece>>Init(std::shared_ptr<PieceSignalDirector> signalDirector);
	};
}

