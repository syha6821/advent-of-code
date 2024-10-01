#pragma once
#include "point.h"
#include "map.h"

class Sand
{
public:
    Sand(){};
    char fall(Map& map);

private:
    void set_location(Point point);
    Point location = Point(500, 0);
    Point below();
    Point below_left();
    Point below_right();
};

bool is_available_spot(Point point, Map &map);