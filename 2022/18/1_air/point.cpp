#include "point.h"

int Point::distance(Point point)
{
    return sqrt(pow((x() - point.x()),2) + pow(y() - point.y(),2) + pow(z() - point.z(),2));
}

ostream &operator<<(ostream &stream, const Point &point)
{
    stream << '(';
    for (int i = 0; i < point.coordinates().size() - 1; i++)
    {
        stream << point.coordinates()[i] << ',';
    }
    stream << point.coordinates().back() << ')';

    return stream;
};
