#pragma once
#include "std_lib_facilities.h"
#include "position.h"
#include "material.h"
#include "direction.h"

vector<vector<char>> rotated(const vector<vector<char>>& square);

class Map
{
public:
    Map(const vector<vector<char>>& m):map_(m), rotated_map_(rotated(m)){};
    Position start_position() const;
    int width() const { return map_[0].size(); };
    int height() const { return map_.size(); };
    char at(const Position& pos) const { return map_[pos.row()][pos.column()]; };
    Position LinkedPosition(const Position& position, Direction direction) const;

    Position find_first_not_empty(const vector<vector<char>> &map, int row_num) const;
    Position find_last_not_empty(const vector<vector<char>> &map, int row_num) const;

    Position RightRotatedPosition(const Position &pos) const { return Position(pos.column(), width() - 1 - pos.row()); };
    Position LeftRotatedPosition(const Position &pos) const { return Position(height() - 1 - pos.column(), pos.row()); };

    friend ostream &operator<<(ostream &stream, const Map &map);

private:
    vector<vector<char>> map_;
    vector<vector<char>> rotated_map_;
};
