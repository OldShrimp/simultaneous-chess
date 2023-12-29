#include "Knight.h"

void Knight::generateValidMoves()
{
	validMoves.clear();

	std::vector<std::pair<int, int>> directions;
	directions.push_back(std::make_pair(2, 1));
	directions.push_back(std::make_pair(2, -1));
	directions.push_back(std::make_pair(-2, 1));
	directions.push_back(std::make_pair(-2, -1));
	directions.push_back(std::make_pair(1, 2));
	directions.push_back(std::make_pair(1, -2));
	directions.push_back(std::make_pair(-1, 2));
	directions.push_back(std::make_pair(-1, -2));
	for (auto& i : directions) // standard movement
	{
		auto dest = std::make_pair(pos.first + i.first, pos.second + i.second);
		if (in_bounds(dest))
		{
			if (!is_occupied(dest))
			{
				validMoves.push_back(dest);
			}
			else if (is_enemy(dest))
				validMoves.push_back(dest);
		}
	}
}