#ifndef Piece_H
#define Piece_H
#include <vector>

class Piece
{
public:
	Piece(char _type, int _value, bool _team, std::pair<int, int> _pos, class ChessBoard* _board);
	~Piece();
	std::vector<std::pair<int, int>> getValidMoves() const;
	std::pair<int, int> getPosition() const { return pos; }
	void update();
	void setPosition(std::pair<int, int> p) { pos = p; _hasMoved = true; } // maybe add error checking here
	bool hasMoved() const { return _hasMoved; }
	const char type;
	const bool team;
	const int value;
protected:
	std::pair<int, int> pos;
	int lastUpdate;
	bool _hasMoved;
	std::vector<std::pair<int, int>> validMoves;
	class ChessBoard* board;
	virtual void generateValidMoves() = 0;
	void checkValidation();
	bool in_bounds(std::pair<int, int> p);
	bool is_occupied(std::pair<int, int> p);
	bool is_enemy(std::pair<int, int> p);
};
#endif