#pragma once
#include "std_lib_facilities.h"

class Position
{
public:
    Position(int row, int column):row_(row),column_(column){};
    int row() const { return row_; };
    int column() const { return column_; };
    friend ostream &operator<<(ostream &stream, const Position& position);

private:
    int row_;
    int column_;
};