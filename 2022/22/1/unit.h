#pragma once
#include "map.h"
#include "position.h"
#include "direction.h"

class Unit
{
public:
    Unit(const Map& map):map_(map), location_(map.start_position()){};
    char Look(Direction direction) const;
    bool Move(Direction direction);
    Position PositionAt(Direction direction) const;

private:
    Map map_;
    Position location_;
};

void MovePattern(const vector<pair<char, int>>& patterns, Unit unit);