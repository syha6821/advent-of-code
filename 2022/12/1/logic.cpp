#include "logic.h"

int find_fewest_step(Map& map,vector<Unit> units)
{
    vector<Unit> next_units;
    for(Unit unit : units)
    {
        if(unit.location().is_end())
        {
            cout << "is end\n";
            return unit.get_path().size() - 1;
        }
        else
        {
            for(Point point : unit.get_around())
            {
                if (not map.is_valid_point(point)) continue;
                Area& next_area = map.get_area(point);
                if (not unit.is_approachable(next_area)) continue;
                if (next_area.is_stepped()) continue;

                next_units.push_back(Unit(unit, next_area));
            }
        }
    }
    return find_fewest_step(map, next_units);
}

int find_nearest_a_from_end(Map& map,vector<Unit> units)
{
    vector<Unit> next_units;
    for(Unit unit : units)
    {
        if(unit.location().get_height() == 'a')
        {
            cout << "yah!\n";
            return unit.get_path().size() - 1;
        }
        else
        {
            for(Point point : unit.get_around())
            {
                if (not map.is_valid_point(point)) continue;
                Area& next_area = map.get_area(point);
                if (not unit.is_descendible(next_area)) continue;
                if (next_area.is_stepped()) continue;

                next_units.push_back(Unit(unit, next_area));
            }
        }
    }
    return find_nearest_a_from_end(map, next_units);
}