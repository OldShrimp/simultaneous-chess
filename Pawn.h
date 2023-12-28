#ifndef Pawn_H
#define Pawn_H
#include "Piece.h"

class Pawn :
    public Piece
{
public:
	Pawn(bool _team, std::pair<int, int> _pos, ChessBoard* _board) : Piece('p', 1, _team, _pos, _board) {}
protected:
	void generateValidMoves();
};

#endif