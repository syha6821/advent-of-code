#pragma once
#include "std_lib_facilities.h"
#include "area.h"
#include "map.h"

class Unit
{
public:
    Unit(Area& area)
    {
        area.check_stepped();
        path.push_back(area);
    };
    Unit(Unit before, Area& area) : path(before.get_path())
    {
        area.check_stepped();
        path.push_back(area);
    };

    Point up() { return Point(location().get_point().x, location().get_point().y - 1); };
    Point down() { return Point(location().get_point().x, location().get_point().y + 1); };
    Point right() { return Point(location().get_point().x + 1, location().get_point().y); };
    Point left() { return Point(location().get_point().x - 1, location().get_point().y); };
    vector<Point> get_around() { return vector<Point>({up(), down(), right(), left()}); };

    vector<Area> get_path() { return path; };
    Area location() { return path.back(); };
    bool is_approachable(Area next_area)
    {
        return not((next_area.get_height() - this->location().get_height()) > 1);
    }
    
    bool is_descendible(Area next_area)
    {
        return ((this->location().get_height() - next_area.get_height()) <= 1);
    }
    

private:
    vector<Area> path;
};