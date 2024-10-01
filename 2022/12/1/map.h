#pragma once
#include "std_lib_facilities.h"
#include "area.h"
#include <tuple>

class Map
{
public:
    Map(const vector<vector<Area>> &device_data, Point s, Point e) : grid(device_data), start(s), end(e), width(grid[0].size()), height(grid.size()){};
    Area& get_area(Point point) { return grid[point.y][point.x]; }
    Area& get_start() { return grid[start.y][start.x]; };
    Area& get_end() {return grid[end.y][end.x]; };
    bool is_valid_point(Point point);

private:
    vector<vector<Area>> grid;
    const int width;
    const int height;
    Point start;
    const Point end;
};