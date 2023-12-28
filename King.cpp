#include "King.h"
#include "ChessBoard.h"

void King::generateValidMoves()
{
	validMoves.clear();
	auto state = board->getBoardState();

	auto in_bounds = [](std::pair<int, int> p) { return p.first >= 0 && p.first < BOARDSIZE && p.second >= 0 && p.second < BOARDSIZE; };
	auto is_occupied = [&state](std::pair<int, int> p) { return state[p.first][p.second] != nullptr; };
	auto is_enemy = [&state, this](std::pair<int, int> p) { return state[p.first][p.second]->team != team; };

	for (int i = -1; i < 2; i++) // standard movement
		for (int j = -1; j < 2; j++)
		{
			auto dest = std::make_pair(pos.first + i, pos.second + j);
			if (in_bounds(dest) && is_occupied(dest) && is_enemy(dest))
				validMoves.push_back(dest);
		}
	// castling
}