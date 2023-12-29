#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
	Knight(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('n', 3, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

