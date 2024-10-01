#pragma once
#include "std_lib_facilities.h"
#include "position.h"
#include "material.h"
#include "direction.h"
#include "area.h"
#include "line.h"
#include "side.h"

class Map
{
public:
    Map(const vector<vector<Area>>& m);
    Position start_position() const;
    int width() const { return map_[0].size(); };
    int height() const { return map_.size(); };
    Area& at(const Position& pos) { return map_[pos.row()][pos.column()]; };
    Position LinkedPosition(const Position& position, Direction& direction);
    vector<Line> lines() const { return lines_; };

    friend ostream &operator<<(ostream &stream, const Map &map);

private:
    vector<Line> lines_;
    vector<Point> default_points_ = {Point(0,1,0), Point(1,1,0), Point(1,0,0), Point(0,0,0)};
    Position find_first_not_empty(int row_num) const;
    vector<vector<Area>> map_;

    void ReadLines(Position top_left_position, const Side& side, Direction before_direction);
    void ReadLines_(Position top_left_position, const Side& side, Direction before_direction);
    bool is_valid_position(const Position& pos);
};
