#pragma once
#include "std_lib_facilities.h"
#include "point.h"
#include "direction.h"
#include "area.h"
#include "position.h"

class Line
{
public:
    Line(pair<Point, Point> points, Direction direction);
    string name() const { return name_; };
    void AddArea(Area& area);
    Position at(int index) { return areas_.at(index)->pos(); };
    Position at_last() { return areas_.back()->pos(); };
    friend ostream &operator<<(ostream &stream, const Line &line);
    string reverse_name() const { return reverse_name_; };
    Direction direction() const { return direction_; };

private:
    string name_;
    string reverse_name_;
    const Direction direction_;
    vector<Area*> areas_;
};

inline ostream &operator<<(ostream &stream, const Line &line)
{
    stream << line.name().substr(0,3) << ", " << line.name().substr(3) << ' ' << direction_string(line.direction_);
    return stream;
}