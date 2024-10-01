#include "cube.h"

Cube::Cube(int x, int y, int z) : x_(x), y_(y), z_(z)
{
    sides_.insert(Side(set<Point>({
        Point({x,y,z}),Point({x,y+1,z}),Point({x+1,y+1,z}),Point({x+1,y,z})
    })));
    sides_.insert(Side(set<Point>({
        Point({x+1,y,z}),Point({x+1,y+1,z}),Point({x+1,y+1,z+1}),Point({x+1,y,z+1})
    })));
    sides_.insert(Side(set<Point>({
        Point({x+1,y,z+1}),Point({x+1,y+1,z+1}),Point({x,y+1,z+1}),Point({x,y,z+1})
    })));
    sides_.insert(Side(set<Point>({
        Point({x,y,z+1}),Point({x,y+1,z+1}),Point({x,y+1,z}),Point({x,y,z})
    })));
    sides_.insert(Side(set<Point>({
        Point({x,y+1,z}),Point({x,y+1,z+1}),Point({x+1,y+1,z+1}),Point({x+1,y+1,z})
    })));
    sides_.insert(Side(set<Point>({
        Point({x,y,z+1}),Point({x,y,z}),Point({x+1,y,z}),Point({x+1,y,z+1})
    })));
}

ostream &operator<<(ostream &stream, const Cube &cube)
{
    stream << '(' << cube.x_ << ',' << cube.y_ << ',' << cube.z_ << ')';
    return stream;
}