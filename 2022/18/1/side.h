#pragma once
#include "std_lib_facilities.h"
#include "point.h"
#include <set>

class Side
{
public:
    Side(set<Point> points):points_(points){
        lines_ = make_lines();
    };
    const set<Point>& points() const { return points_; };

    friend ostream &operator<<(ostream &stream, const Side &side);
    
    Point center();

    vector<set<Point>> lines() { return lines_; };
    vector<Side> AdjacentSides();

    bool operator==(const Side& side) const
    {
        return points_ == side.points();
    }

private:
    vector<set<Point>> make_lines();
    vector<set<Point>> lines_;
    set<Point> points_;
};

namespace std
{
    template<>
    struct hash<Side>
    {
        size_t operator()(const Side& side) const
        {
            int sum_of_x = 0;
            int sum_of_y = 0;
            for (Point point : side.points())
            {
                sum_of_x += point.coordinates()[0];
                sum_of_y += point.coordinates()[1];
            }

            return sum_of_x + sum_of_y;
        }
    };
}