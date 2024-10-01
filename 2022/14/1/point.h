#pragma once
#include "std_lib_facilities.h"

struct Point
{
public:
    Point(int xx, int yy) : x(xx), y(yy){};
    Point(pair<int, int> p) : x(p.first), y(p.second){};
    int get_x() const {return x;};
    int get_y() const {return y;};
    int x;
    int y;
    bool operator==(const Point& point)const
    {
        return point.get_x() == x && point.get_y() == y;
    }
};

template<>
struct hash<Point>
{
    size_t operator()(const Point &point) const
    {
        int x = point.x;
        int y = point.y;
        return (x >= y) ? (x * x + x + y) : (x + y * y);
    }
};