#include "Rook.h"
#include "ChessBoard.h"

void Rook::generateValidMoves()
{
	validMoves.clear();

	std::vector<std::pair<int, int>> directions;
	directions.push_back(std::make_pair(-1, 0));
	directions.push_back(std::make_pair(1, 0));
	directions.push_back(std::make_pair(0, 1));
	directions.push_back(std::make_pair(0, -1));
	for (auto& i : directions) // standard movement
	{
		auto dest = std::make_pair(pos.first + i.first, pos.second + i.second);
		while (true)
		{
			if (in_bounds(dest))
			{
				if (!is_occupied(dest)) // stop after hitting an enemy
				{
					validMoves.push_back(dest);
					break;
				}
				else if (is_enemy(dest))
					validMoves.push_back(dest);
				else
					break;
			}
			else
				break;
			dest.first += i.first;
			dest.second += i.second;
		}
	}
}