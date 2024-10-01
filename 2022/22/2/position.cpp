#include "position.h"

ostream &operator<<(ostream &stream, const Position &position)
{
    stream << '(' << position.row_ << ',' << position.column_ << ')';
    return stream;
}