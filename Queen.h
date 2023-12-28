#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
	Queen(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('q', 9, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

