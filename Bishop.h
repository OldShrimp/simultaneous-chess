#pragma once
#include "Piece.h"

class Bishop :
    public Piece
{
public:
	Bishop(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('b', 3, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

