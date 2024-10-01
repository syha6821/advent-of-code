#pragma once
#include "std_lib_facilities.h"

enum class Direction
{
    N, S, W, E, Current
};

inline vector<Direction> default_direction()
{
    return {Direction::N, Direction::S, Direction::W, Direction::E};
}

inline vector<Direction> next_direction(const vector<Direction>& direction)
{
    return {direction.at(1), direction.at(2), direction.at(3), direction.at(0)};
}