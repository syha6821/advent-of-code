#pragma once
#include "std_lib_facilities.h"
#include "position.h"
#include <unordered_set>
#include <unordered_map>

class Elf
{
public:
    Elf(Position pos, int name) : pos_(pos), name_(name){};
    Position pos() const { return pos_; };
    void move(Position pos) { pos_ = pos; };
    int name() const { return name_; };

    bool operator==(const Elf &elf) const
    {
        return name_ == elf.name_;
    }

    bool can_move(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const;
    bool not_move(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const;
    Position propose(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const;
    
private:
    bool is_empty_direction(const unordered_set<Position> &elves_positions, const Direction& direction) const;
    Direction next_empty_direction(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const;
    vector<Direction> empty_directions(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const;

    Position pos_;
    int name_;

};

namespace std
{
    template<>
    struct hash<Elf>
    {
        
        hash<int> hasher;
        size_t operator()(const Elf& elf) const
        {
            return hasher(elf.name());
        }
    };
}

unordered_set<Position> elves_positions(const unordered_set<Elf>& elves);

unordered_map<Position, vector<Elf>> proposed_positions(const unordered_set<Elf>& elves, const vector<Direction>& look_order);

unordered_set<Elf> not_moving_elves(const unordered_set<Elf>& elves, const vector<Direction>& look_order);

int expand(const unordered_set<Elf>& elves, const vector<Direction>& look_order, int round);