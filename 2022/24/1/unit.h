#pragma once
#include "map.h"
#include "position.h"
#include <unordered_set>

class Unit
{
public:
    Unit(const Map& map);
    vector<Position> around_positions();
    void MoveTo(Position pos) { pos_ = pos; };
    bool IsAdjacentTo(Position pos) { return (abs(pos_.row() - pos.row()) + abs(pos_.column() - pos.column()) == 1); };

    Position pos() const { return pos_; };
    Position start_pos() const { return start_position_; };
    Position end_pos() const { return end_position_; };
    
    void reverse_start_position()
    {
        pos_ = end_position_;
        swap(start_position_, end_position_);
    }

    bool operator==(const Unit& unit) const
    {
        return pos_ == unit.pos();
    }

private:
    Position start_position_;
    Position end_position_;
    Position pos_;
};

int FindPath(int round, unordered_set<Unit> units, vector<Blizzard>& blizzards, const Map &map);
int FindPathReverse(int round, unordered_set<Unit> units, vector<Blizzard>& blizzards, const Map &map);

namespace std
{
    template<>
    struct hash<Unit>
    {
        
        hash<int> hasher;
        size_t operator()(const Unit& unit) const
        {
            return unit.pos().row();
        }
    };
}