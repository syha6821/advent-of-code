#include "map.h"

unordered_set<Position> Map::safe_positions(const vector<Blizzard> &blizzards) const
{
    unordered_set<Position> map;
    map.insert(START);
    map.insert(END);
    for (int row = 1; row <= HEIGHT; row++)
   {
        for (int column = 1; column <= WIDTH; column++)
        {
            map.insert(Position(row, column, WIDTH, HEIGHT));
        }
    }
    for (const Blizzard& blizzard : blizzards)
    {
        map.erase(blizzard.pos());
    }
    return map;
}

bool Map::is_valid_pos(const Position &pos) const
{
    return ((0 <= pos.row()) && (pos.row() <= HEIGHT) && (0 <= pos.column()) && (pos.column() <= WIDTH)) || (pos == START) || (pos == END);
}
