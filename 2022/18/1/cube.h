#pragma once
#include "std_lib_facilities.h"
#include <unordered_set>
#include "side.h"
#include <set>
#include "point.h"

class Cube
{
public:
    Cube(int x, int y , int z);
    int x() const { return x_; };
    int y() const { return y_; };
    int z() const { return z_; };
    const unordered_set<Side>& sides() const { return sides_; };

    bool operator==(const Cube& cube) const
    {
        return sides_ == cube.sides();
    }

    friend ostream &operator<<(ostream &stream, const Cube &cube);

private:
    unordered_set<Side> sides_;
    int x_;
    int y_;
    int z_;
};

namespace std
{
    template<>
    struct hash<Cube>
    {
        size_t operator()(const Cube& cube) const
        {
            return cube.x() + cube.y() + cube.z();
        }
    };
}