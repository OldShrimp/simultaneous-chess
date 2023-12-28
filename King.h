#pragma once
#include "Piece.h"

class King :
    public Piece
{
public:
	King(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('k', 0, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

