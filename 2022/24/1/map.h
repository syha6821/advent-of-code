#pragma once
#include "std_lib_facilities.h"
#include "position.h"
#include "blizzard.h"
#include <unordered_set>

class Map
{
public:
    Map(int width,int height):WIDTH(width),HEIGHT(height),START(Position(0,1)), END(height + 1, width){};
    int width() const { return WIDTH; };
    int height() const { return HEIGHT; };
    unordered_set<Position> safe_positions(const vector<Blizzard>& blizzards) const;
    bool is_valid_pos(const Position& pos) const;
    void reverse_start_point() { swap(START, END); };

private:
    Position START;
    Position END;
    const int WIDTH;
    const int HEIGHT;
};