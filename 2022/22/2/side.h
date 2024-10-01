#pragma once
#include "point.h"
#include "line.h"

class Side
{
public:
    const static int WIDTH;
    Side(const vector<Point>& points);
    Point top_left() const { return points_.at(0); };
    Point top_right() const { return points_.at(1); };
    Point bottom_right() const { return points_.at(2); };
    Point bottom_left() const { return points_.at(3); };
    
    Line up() const { return Line(make_pair(top_left(), top_right()), Direction::Up);};
    Line right() const { return Line(make_pair(top_right(), bottom_right()), Direction::Right);};
    Line down() const { return Line(make_pair(bottom_right(), bottom_left()), Direction::Down);};
    Line left() const { return Line(make_pair(bottom_left(), top_left()), Direction::Left);};
    
    Side adjacent_up_side() const;
    Side adjacent_down_side() const;
    Side adjacent_right_side() const;
    Side adjacent_left_side() const;

private:
    enum Type
    {
        Front, Back, Top, Base, LeftSide, RightSide,
    };

    Type type_;
    vector<Point> points_;
};