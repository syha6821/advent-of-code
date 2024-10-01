#pragma once
#include "direction.h"

class Position
{
public:
    Position(int row, int column) : row_(row), column_(column){};
    int row() const { return row_; };
    int column() const { return column_; };

    bool operator==(const Position &pos) const
    {
        return row_ == pos.row_ && column_ == pos.column_;
    }
    
    Position at(Direction direction) const
    {
        switch (direction)
        {
        case Direction::N:
            return N();
        case Direction::S:
            return S();
        case Direction::W:
            return W();
        case Direction::E:
            return E();
        default:
            error("Not valid direction (Position::at())");
            return *this;
        }
    }

    vector<Position> positions_at(Direction direction) const
    {
        if(direction == Direction::N) return Ns();
        if(direction == Direction::S) return Ss();
        if(direction == Direction::E) return Es();
        if(direction == Direction::W) return Ws();
        else
        {
            error("Not valid direction (positions_at())");
            return {};
        }
    };

    vector<Position> Ns() const { return {N(), NW(), NE()}; };
    vector<Position> Ss() const { return {S(), SW(), SE()}; };
    vector<Position> Ws() const { return {W(), NW(), SW()}; };
    vector<Position> Es() const { return {E(), NE(), SE()}; };

    Position N() const { return Position(row_ - 1, column_); };
    Position S() const { return Position(row_ + 1, column_); };
    Position W() const { return Position(row_, column_ - 1); };
    Position E() const { return Position(row_, column_ + 1); };

    Position NW() const { return Position(row_ - 1, column_ - 1); };
    Position NE() const { return Position(row_ - 1, column_ + 1); };
    Position SW() const { return Position(row_ + 1, column_ - 1); };
    Position SE() const { return Position(row_ + 1, column_ + 1); };

private:
    int row_ = 0;
    int column_ = 0;

};

namespace std
{
    template<>
    struct hash<Position>
    {
        
        size_t operator()(const Position& pos) const
        {
            return pos.row();
        }
    };
}