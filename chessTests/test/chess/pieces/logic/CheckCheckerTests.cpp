#include "../../../../../chess/src/chess/logic/Coordinate.h"
#include "../../../../../chess/src/chess/pieces/King.h"
#include "../../../../../chess/src/chess/pieces/logic/CheckChecker.h"
#include "../../../../../chess/src/chess/pieces/Rook.h"

#include <boost/test/unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE(MoveCheckerTests)

BOOST_AUTO_TEST_CASE(Check_Test)
{
	auto blackRook = std::make_shared<Chess::Rook>(Chess::ePieceColor::BLACK, 1);
	auto whiteKing = std::make_shared<Chess::King>(Chess::ePieceColor::WHITE);
	auto whiteRook = std::make_shared<Chess::Rook>(Chess::ePieceColor::WHITE, 1);
	auto checker = std::make_shared<Chess::CheckChecker>();

	std::vector<std::shared_ptr<Chess::Piece>> pieces = { blackRook, whiteRook, whiteKing };

	BOOST_CHECK(!checker->IsCheck(whiteKing, pieces));
	BOOST_CHECK(!checker->IsCheck(whiteRook->GetColorAndType().GetColor(), pieces));

	blackRook->Move(Chess::Coordinate(whiteKing->GetPosition().GetFile(), whiteKing->GetPosition().GetRank() - 1));

	BOOST_CHECK(checker->IsCheck(whiteKing, pieces));
	BOOST_CHECK(checker->IsCheck(whiteRook->GetColorAndType().GetColor(), pieces));
}

BOOST_AUTO_TEST_SUITE_END()