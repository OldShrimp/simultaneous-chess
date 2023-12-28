#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
	Rook(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('r', 5, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

