#pragma once
#include "cube.h"
#include <unordered_set>

class Droplet
{
public:
    Droplet(unordered_set<Cube> cubes);
    unordered_set<Side> Surface();
    int surface_size() { return sides_.size(); };
    void spread(unordered_set<Cube> steams);
    void spreader();
    Side just() { return *sides_.begin(); };
    int stepped_size() { return stepped_sides_.size(); };
    unordered_set<Cube> bottom() { return bottom_; };
    unordered_set<Cube> starting_steams();

private:
    bool is_valid(Side side);
    bool is_valid_steam(const Cube& steam);
    unordered_set<Cube> spread_steam(const Cube &cube);

    int max_x_ = 0;
    int max_y_ = 0;
    int max_z_ = 0;
    
    int min_x_ = 0;
    int min_y_= 0;
    int min_z_ = 0;


    unordered_set<Cube> cubes_;
    unordered_set<Side> sides_;
    unordered_set<Side> stepped_sides_;
    unordered_set<Cube> used_steams_;
    unordered_set<Cube> bottom_;
};