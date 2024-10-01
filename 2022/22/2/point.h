#pragma once
#include "std_lib_facilities.h"

class Point
{
public:
    Point(int x, int y, int z):x_(x), y_(y), z_(z){};
    int x() const { return x_; };
    int y() const { return y_; };
    int z() const { return z_; };
    string to_string() const { return std::to_string(x_) + std::to_string(y_) + std::to_string(z_); };
    friend ostream &operator<<(ostream &stream, const Point &line);

private:
    const int x_;
    const int y_;
    const int z_;
};

inline ostream &operator<<(ostream &stream, const Point &line)
{
    stream << '(' << line.x_ << ',' << line.y_ << ',' << line.z_ << ')';
    return stream;
}