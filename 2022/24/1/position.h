#pragma once
#include "std_lib_facilities.h"
#include "direction.h"

class Position
{
public:
    Position(int row, int column, int max_width, int max_height) : row_(row), column_(column), max_width_(max_width), max_height_(max_height){};
    Position(int row, int column) : row_(row), column_(column){};
    int row() const { return row_; };
    int column() const { return column_; };

    void Move(Direction Direction);

    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    
    Position atUp() const;
    Position atRight() const;
    Position atDown() const;
    Position atLeft() const;

    bool operator==(const Position& pos) const
    {
        return row_ == pos.row_ && column_ == pos.column_;
    }

    friend ostream &operator<<(ostream &os, const Position &pos);

private:
    int row_;
    int column_;

    int max_width_;
    int max_height_;
};

namespace std
{
    template<>
    struct hash<Position>
    {
        
        hash<int> hasher;
        size_t operator()(const Position& pos) const
        {
            return pos.row();
        }
    };
}