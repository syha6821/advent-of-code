#pragma once
#include "std_lib_facilities.h"

class Beacon
{
public:
    Beacon(int xx, int yy):x(xx),y(yy){};
    Beacon(pair<int,int> xy):x(xy.first),y(xy.second){};
    int get_x() const { return x; };
    int get_y() const { return y; };
    bool operator<(const Beacon& beacon) const
    {
        return (beacon.get_x() < x) || (beacon.get_y() < y);
    }

private:
    int x;
    int y;
};
