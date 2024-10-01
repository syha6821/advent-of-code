#pragma once
#include "cube.h"
#include <unordered_set>

class Droplet
{
public:
    Droplet(unordered_set<Cube> cubes):cubes_(cubes), sides_(Surface()){};
    unordered_set<Side> Surface();
    set<set<Point>> duplicate_lines();
    int surface_size() { return sides_.size(); };
    void spread(unordered_set<Side> sides);
    void spreader();
    Side just() { return *sides_.begin(); };
    int stepped_size() { return stepped_sides_.size(); };

private:
    vector<Side> possible_ways_from(Side &side);
    bool is_valid(Side side);
    unordered_set<Cube> cubes_;
    unordered_set<Side> sides_;
    unordered_set<Side> stepped_sides_;
};