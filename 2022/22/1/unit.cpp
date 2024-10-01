#include "unit.h"

char Unit::Look(Direction direction) const
{
    return map_.at(PositionAt(direction));
}

Position Unit::PositionAt(Direction direction) const
{
    switch (direction)
    {
    case Direction::Left:
        return Position(location_.row(), location_.column() - 1);

    case Direction::Right:
        return Position(location_.row(), location_.column() + 1);

    case Direction::Up:
        return Position(location_.row() - 1, location_.column());

    case Direction::Down:
        return Position(location_.row() + 1, location_.column());
    
    case Direction::Current:
        return location_;

    default:
        return location_;
    }
}

bool Unit::Move(Direction direction)
{
    if(Look(direction) == (char)Material::Rock)
    {
        return false;
    }
    if(Look(direction) == (char)Material::Empty)
    {
        Position destination = map_.LinkedPosition(location_, direction);
        if(map_.at(destination) == (char)Material::Rock)
        {
            return false;
        }
        location_ = destination;
        cout << location_ << '\n';
        return true;
    }

    location_ = PositionAt(direction);
    cout << location_ << '\n';
    return true;
}

void ChangeDirection(Direction& direction,char rotate)
{
    if(rotate == 'R')
    {
        direction = Direction(((int)direction + 1) % 4);
    }
    else if(rotate == 'L')
    {
        direction = Direction(((int)direction + 3) % 4);
    }
}

void MovePattern(const vector<pair<char, int>>& patterns, Unit unit)
{
    Direction direction = Direction::Up;
    for(auto pattern : patterns)
    {
        char rotate = pattern.first;
        int count = pattern.second;
        ChangeDirection(direction, rotate);
        
        cout << "Rotate : " << rotate << '\n';
        cout << "Count : " << count << '\n';
        while(count != 0 && unit.Move(direction))
        {
            count--;
        }
    }
    
    Position last_position = unit.PositionAt(Direction::Current);
    int password = last_position.row() * 1000 + last_position.column() *  4 + direction_value(direction);
    cout << "password : " << password << '\n';
}