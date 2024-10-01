#pragma once
#include "std_lib_facilities.h"

class Point
{
public:
    Point(vector<int> coordinates):coordinates_(coordinates){};
    const vector<int>& coordinates() const { return coordinates_; };

    int distance(Point point);

    const int x() { return coordinates_[0]; };
    const int y() { return coordinates_[1]; };
    const int z() { return coordinates_[2]; };

    bool operator==(const Point& point) const
    {
        return coordinates_ == point.coordinates();
    };

    bool operator<(const Point& point) const
    {
        return coordinates_ < point.coordinates();
    };

    friend ostream &operator<<(ostream &stream, const Point &point);

private:
    vector<int> coordinates_;
};
