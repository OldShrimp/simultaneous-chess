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
			if (in_bounds(dest) && ((is_occupied(dest) && is_enemy(dest)) || !is_occupied(dest)))
				validMoves.push_back(dest);
		}
	if (!hasMoved() && !board->checkCheck(team)) // castling
	{
		auto rookpos = std::make_pair(0, pos.second);
		if (is_occupied(rookpos) && !state[rookpos.first][rookpos.second]->hasMoved()) // left side
		{
			if (!is_occupied(std::make_pair(3, pos.second)) && !is_occupied(std::make_pair(2, pos.second)) && !is_occupied(std::make_pair(1, pos.second)))
			{
				auto temp3 = state;
				temp3[pos.first][pos.second] = nullptr;
				temp3[3][pos.second] = this;

				auto temp2 = state;
				temp2[pos.first][pos.second] = nullptr;
				temp2[2][pos.second] = this;

				if (!board->checkCheck(temp2, team) && !board->checkCheck(temp3, team))
					validMoves.push_back(std::make_pair(2, pos.second));
			}
		}
		if (is_occupied(rookpos) && !state[rookpos.first][rookpos.second]->hasMoved()) // right side
		{
			if (!is_occupied(std::make_pair(5, pos.second)) && !is_occupied(std::make_pair(6, pos.second)))
			{
				auto temp5 = state;
				temp5[pos.first][pos.second] = nullptr;
				temp5[5][pos.second] = this;

				auto temp6 = state;
				temp6[pos.first][pos.second] = nullptr;
				temp6[6][pos.second] = this;

				if (!board->checkCheck(temp5, team) && !board->checkCheck(temp6, team))
					validMoves.push_back(std::make_pair(2, pos.second));
			}
		}
	}
}