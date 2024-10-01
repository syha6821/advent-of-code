#include "position.h"

ostream &operator<<(ostream &os, const Position &pos)
{
    os << '(' << pos.row_ << ',' << pos.column_ << ')';
    return os;
}

void Position::Move(Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        MoveUp();
        break;
    case Direction::Right:
        MoveRight();
        break;
    case Direction::Down:
        MoveDown();
        break;
    case Direction::Left:
        MoveLeft();
        break;
    
    default:
        error("Invalid Direction at Position::Move()");
        MoveUp();
        break;
    }
}

void Position::MoveUp()
{
    if(row_ == 1)
    {
        row_ = max_height_;
    }
    else
    {
        row_--;
    }
}

void Position::MoveRight()
{
    column_ = (column_ % max_width_) + 1;
}

void Position::MoveDown()
{
    row_ = (row_ % max_height_) + 1;
}

void Position::MoveLeft()
{
    if(column_ == 1)
    {
        column_ = max_width_;
    }
    else
    {
        column_--;
    }
}

Position Position::atUp() const
{
    Position pos = *this;
    pos.MoveUp();
    return pos;
}

Position Position::atRight() const
{
    Position pos = *this;
    pos.MoveRight();
    return pos;
}

Position Position::atDown() const
{
    Position pos = *this;
    pos.MoveDown();
    return pos;
}

Position Position::atLeft() const
{
    Position pos = *this;
    pos.MoveLeft();
    return pos;
}
