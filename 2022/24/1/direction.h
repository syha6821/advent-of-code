#pragma once
enum class Direction
{
    Up, Right, Down, Left,
};

inline Direction char_to_direction(char ch)
{
    switch (ch)
    {
    case '<':
        return Direction::Left;
    case '>':
        return Direction::Right;
    case 'v':
        return Direction::Down;
    case '^':
        return Direction::Up;
    
    default:
        error("Invalid char at char_to_direction()");
        return Direction::Up;
    }
}