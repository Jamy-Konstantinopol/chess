#include "../../../../chess/src/chess/Sizes.h"
#include "../../../../chess/src/chess/Coordinate.h"
#include "../../../../chess/src/chess/pieces/Bishop.h"
#include "../../../../chess/src/chess/pieces/ePieceColor.h"
#include "../../../../chess/src/chess/pieces/Rook.h"
#include "../../../../chess/src/chess/pieces/RookChecker.h"

#include <boost/test/unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE(MoveCheckerTests)

BOOST_AUTO_TEST_CASE(FindPosibleRookMoves_Test)
{
	auto blackRook = std::make_shared<Chess::Rook>(Chess::ePieceColor::BLACK, 1);
	auto whiteBishop = std::make_shared<Chess::Bishop>(Chess::ePieceColor::WHITE, 1);
	auto whiteRook = std::make_shared<Chess::Rook>(Chess::ePieceColor::WHITE , 1);

	std::vector<std::shared_ptr<Chess::IPiece>> pieces = { blackRook, whiteBishop, whiteRook };
	auto rookChecker = std::make_shared<Chess::RookChecker>();

	BOOST_CHECK_THROW(rookChecker->GetPossibleMoves(whiteBishop, pieces), std::out_of_range);

	blackRook->Move(Chess::Coordinate('A', 7));
	BOOST_CHECK_EQUAL(rookChecker->GetPossibleMoves(whiteRook, pieces).size(), 7);
}

BOOST_AUTO_TEST_SUITE_END()