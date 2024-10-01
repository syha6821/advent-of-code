#pragma once

enum class Direction
{
    Up, Right, Down, Left, Current,
};

inline bool is_vertical(Direction direction)
{
    if (direction == Direction::Up || direction == Direction::Down)
    {
        return true;
    }
    return false;
}

inline bool is_horizontal(Direction direction)
{
    if (direction == Direction::Left || direction == Direction::Right)
    {
        return true;
    }
    return false;
}

inline int direction_value(Direction direction)
{
    switch (direction)
    {
    case Direction::Right:
        return 0;
    case Direction::Down:
        return 1;
    case Direction::Left:
        return 2;
    case Direction::Up:
        return 3;
    default:
        return -1;
    }
}