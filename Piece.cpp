#include "Piece.h"
#include "ChessBoard.h"
#include <iostream>

Piece::Piece(char _type, int _value, bool _team, std::pair<int, int> _pos, ChessBoard* _board) : type(_type), value(_value), team(_team), pos(_pos), board(_board) , lastUpdate(-1)
{
	board->addPiece(this);
	std::cout << "piece " << type << " created at " << pos.first << ',' << pos.second << '\n';
}
Piece::~Piece()
{
	board->removePiece(this);
	std::cout << "piece " << type << " at " << pos.first << ',' << pos.second << " destroyed\n";
}

std::vector<std::pair<int, int>> Piece::getValidMoves() const
{
	return validMoves;
}

void Piece::update()
{
	if (lastUpdate != board->getTurnCount())
	{
		lastUpdate = board->getTurnCount();
		generateValidMoves();
		checkValidation();
	}
}

void Piece::checkValidation()
{
	std::vector<std::pair<int, int>> moves;
	for (auto& m : validMoves)
	{
		auto bState = board->getBoardState(); // check effect this move has on the board
		bState[pos.first][pos.second] = nullptr;
		bState[m.first][m.second] = this;

		if (!board->checkCheck(bState, team)) // cannot put own king in check
			moves.push_back(m);
	}
	validMoves = moves;
}