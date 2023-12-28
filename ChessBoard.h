#ifndef ChessBoard_H
#define ChessBoard_H
#define BOARDSIZE 8

#include "ChessPieces.h"

class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();

	void addPiece(Piece*);
	void removePiece(Piece*);
	void movePiece(Piece*, std::pair<int, int> pos);
	void movePiece(std::pair<int, int> start, std::pair<int, int> fin);
	int getScore(bool t) { return t ? scores.second : scores.first; }

	std::vector<std::vector<const Piece*>> getBoardState();
	std::vector<std::pair<int, int>> checkCheck(bool);

	struct turn // maybe use a pair of single-player turns to clean up some if-statements using get
	{
		turn() : p1_origin(std::make_pair(-1, -1)), p1_destination(p1_origin), p2_origin(p1_origin), p2_destination(p1_origin) { }
		std::pair<int, int> p1_origin, p1_destination;
		std::pair<int, int> p2_origin, p2_destination;
	};
	turn getLastTurn() { return history.size() > 0 ? history.back() : turn(); }
	turn getTurn(int i) { return history[i]; }
	int getTurnCount() const { return history.size(); }
private:
	Piece* board[BOARDSIZE][BOARDSIZE];

	std::vector<turn> history;
	turn currentTurn;
	void nextTurn();
	std::pair<int, int> scores = std::make_pair(0, 0);

	void updatePieces();
};

#endif