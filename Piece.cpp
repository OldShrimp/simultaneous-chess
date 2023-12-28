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
	}
}