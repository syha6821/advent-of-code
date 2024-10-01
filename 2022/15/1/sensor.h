#pragma once
#include "beacon.h"
#include "std_lib_facilities.h"
#include "range.h"

class Sensor
{
public:
    Sensor(int xx, int yy, Beacon bc);
    Sensor(pair<int,int> xy, Beacon bc);
    function<bool(int,int)> contains;
    int get_x() { return x; };
    int get_y() { return y; };
    int get_up() { return up; };
    int get_down() { return down; };
    int get_right() { return right; };
    int get_left() { return left; };
    int cross_y(int yy) { return (up <= yy) && (yy <= down); };
    Range get_range_at_y(int yy) const;
    Beacon get_beacon() { return beacon; };

private:
    Beacon beacon;
    int x;
    int y;
    int up;
    int down;
    int left;
    int right;
    int distance;
};