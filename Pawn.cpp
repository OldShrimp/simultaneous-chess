#include "Pawn.h"
#include "ChessBoard.h"

void Pawn::generateValidMoves()
{
	std::vector<std::pair<int, int>> moves;
	auto state = board->getBoardState();

	int direction = 1;
	if (team == 1)
		direction = -1;

	int X = pos.first, Y = pos.second + direction;
	// check for empty spaces ahead of pawn
	if (pos.second == static_cast<int>(3.5 - 2.5 * direction)) // pawn in starting position
	{
		if (state[X][Y + direction] == nullptr)
			moves.push_back(std::pair<int, int>(X, Y + 1 * direction));
	}
	if (state[X][Y] == nullptr)
		moves.push_back(std::pair<int, int>(X, Y));
	// check for opposing pieces on diagonals
	if (X > 0)
		if (state[X - 1][Y] != nullptr && state[X - 1][Y]->team != this->team)
			moves.push_back(std::pair<int, int>(X - 1, Y));
	if (X + 1 < BOARDSIZE)
		if (state[X + 1][Y] != nullptr && state[X + 1][Y]->team != this->team)
			moves.push_back(std::pair<int, int>(X + 1, Y));
	// see if en passent is possible. 
	//  opponent last moved a pawn 2 spaces from its starting position and ended adjacent to your pawn on the same Y
	auto lastMove = board->getLastTurn();
	Y = pos.second;
	if (team == 0 && lastMove.p2_origin.second == BOARDSIZE - 2 && state[lastMove.p2_destination.first][lastMove.p2_destination.second]->type == 'p'
		&& lastMove.p2_destination.second == Y && lastMove.p2_destination.second == BOARDSIZE - 4) // 
	{
		if (lastMove.p2_destination.first == X - 1 && state[X - 1][Y]->type == 'p')
			moves.push_back(std::pair<int, int>(X - 1, Y + direction));
		else if (lastMove.p2_destination.first == X + 1 && state[X + 1][Y]->type == 'p')
			moves.push_back(std::pair<int, int>(X + 1, Y + direction));
	}
	else if (team == 1 && lastMove.p1_origin.second == 1 && state[lastMove.p1_destination.first][lastMove.p1_destination.second]->type == 'p'
		&& lastMove.p1_destination.second == Y && lastMove.p1_destination.second == 3)
	{
		if (lastMove.p1_destination.first == X - 1 && state[X - 1][Y]->type == 'p')
			moves.push_back(std::pair<int, int>(X - 1, Y + direction));
		else if (lastMove.p1_destination.first == X + 1 && state[X + 1][Y]->type == 'p')
			moves.push_back(std::pair<int, int>(X + 1, Y + direction));
	}

	validMoves = moves;
}