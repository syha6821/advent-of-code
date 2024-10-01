#pragma once
#include "direction.h"
#include "position.h"

class Blizzard
{
public:
    Blizzard(Position pos, Direction direction) : pos_(pos), direction_(direction){};
    void Move() { pos_.Move(direction_); };
    Position pos() const { return pos_; };

private:
    Position pos_;
    Direction direction_;
};
