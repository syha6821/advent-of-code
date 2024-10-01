#include "unit.h"

Unit::Unit(const Map &map):start_position_(Position(0,1)), end_position_(Position(map.height() + 1, map.width())), pos_(start_position_)
{
};

vector<Position> Unit::around_positions()
{
    return {pos_.atUp(), pos_.atRight(), pos_.atDown(), pos_.atLeft()};
}

int FindPath(int round,unordered_set<Unit> units, vector<Blizzard>& blizzards, const Map& map)
{
    /* cout << "round : " << round << " / units : " << units.size() << '\n'; */
    
    for(Blizzard& blizzard : blizzards)
    {
        blizzard.Move();
    }

    unordered_set<Position> safe_positions = map.safe_positions(blizzards);
    unordered_set<Unit> next_units;

    for (const Position &pos : safe_positions)
    {
        for(Unit unit : units)
        {
            if(unit.pos() == pos)
            {
                next_units.insert(unit);
            }
        }
    }

    for (const Position& pos : safe_positions)
    {
        for (Unit unit : units)
        {
            if(map.is_valid_pos(pos) && unit.IsAdjacentTo(pos))
            {
                unit.MoveTo(pos);
                next_units.insert(unit);
            }
        }
    }
    
    round++;

    for(const Unit& unit : units)
    {
        if(unit.pos() == unit.end_pos())
        {
            return round - 1;
        }
    }

    return FindPath(round, next_units, blizzards, map);
}

int FindPathReverse(int round, unordered_set<Unit> units, vector<Blizzard>& blizzards, const Map &map)
{
    cout << "round : " << round << " / units : " << units.size() << '\n';
    
    for(Blizzard& blizzard : blizzards)
    {
        blizzard.Move();
    }
    unordered_set<Position> safe_positions = map.safe_positions(blizzards);

    unordered_set<Unit> next_units;

    for (const Position &pos : safe_positions)
    {
        for(Unit unit : units)
        {
            if(unit.pos() == pos)
            {
                next_units.insert(unit);
            }
        }
    }

    for (const Position& pos : safe_positions)
    {
        for (Unit unit : units)
        {
            if(map.is_valid_pos(pos) && unit.IsAdjacentTo(pos))
            {
                unit.MoveTo(pos);
                next_units.insert(unit);
            }
        }
    }
    
    round++;

    for(const Unit& unit : units)
    {
        if(unit.pos() == unit.end_pos())
        {
            return round - 1;
        }
    }

    return FindPath(round, next_units, blizzards, map);
}
