#include "side.h"

pair<char, int> unchanged_coords(const vector<Point>& points)
{
    vector<int> xyz = {0, 0, 0};
    for(const Point& point : points)
    {
        xyz[0] += point.x();
        xyz[1] += point.y();
        xyz[2] += point.z();
    }
    if(xyz[0] % 4 == 0) return make_pair('x', xyz[0] / 4);
    if(xyz[1] % 4 == 0) return make_pair('y', xyz[1] / 4);
    if(xyz[2] % 4 == 0) return make_pair('z', xyz[2] / 4);
}

Side::Side(const vector<Point>& points) : points_(points) { }

Side Side::adjacent_up_side() const
{
    vector<Point> next_points;
    pair<char, int> coords = unchanged_coords(points_);
    Point b_left = top_left();
    Point b_right = top_right();

    if(coords.first == 'x')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(b_left.x() + 1, b_left.y(), b_left.z()));
            next_points.push_back(Point(b_right.x() + 1, b_right.y(), b_right.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(b_left.x() - 1, b_left.y(), b_left.z()));
            next_points.push_back(Point(b_right.x() - 1, b_right.y(), b_right.z()));
        }
    }
    if(coords.first == 'y')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(b_left.x(), b_left.y() + 1, b_left.z()));
            next_points.push_back(Point(b_right.x(), b_right.y() + 1, b_right.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(b_left.x(), b_left.y() - 1, b_left.z()));
            next_points.push_back(Point(b_right.x(), b_right.y() - 1, b_right.z()));
        }
    }
    if(coords.first == 'z')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(b_left.x(), b_left.y(), b_left.z() + 1));
            next_points.push_back(Point(b_right.x(), b_right.y(), b_right.z() + 1));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(b_left.x(), b_left.y(), b_left.z() - 1));
            next_points.push_back(Point(b_right.x(), b_right.y(), b_right.z()- 1));
        }
    }
    next_points.push_back(b_right);
    next_points.push_back(b_left);
    return Side(next_points);
}

Side Side::adjacent_down_side() const
{
    vector<Point> next_points;
    pair<char, int> coords = unchanged_coords(points_);
    Point t_left = bottom_left();
    Point t_right = bottom_right();

    next_points.push_back(t_left);
    next_points.push_back(t_right);

    if(coords.first == 'x')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x() + 1, t_right.y(), t_right.z()));
            next_points.push_back(Point(t_left.x() + 1, t_left.y(), t_left.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x() - 1, t_right.y(), t_right.z()));
            next_points.push_back(Point(t_left.x() - 1, t_left.y(), t_left.z()));
        }
    }
    if(coords.first == 'y')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x(), t_right.y() + 1, t_right.z()));
            next_points.push_back(Point(t_left.x(), t_left.y() + 1, t_left.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x(), t_right.y() - 1, t_right.z()));
            next_points.push_back(Point(t_left.x(), t_left.y() - 1, t_left.z()));
        }
    }
    if(coords.first == 'z')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x(), t_right.y(), t_right.z() + 1));
            next_points.push_back(Point(t_left.x(), t_left.y(), t_left.z() + 1));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x(), t_right.y(), t_right.z()- 1));
            next_points.push_back(Point(t_left.x(), t_left.y(), t_left.z() - 1));
        }
    }
    return Side(next_points);
}

Side Side::adjacent_right_side() const
{
    vector<Point> next_points;
    pair<char, int> coords = unchanged_coords(points_);
    Point t_left = top_right();
    Point b_left = bottom_right();
    
    if(coords.first == 'x')
    {
        if(coords.second == 0)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x() + 1, t_left.y(), t_left.z()));
            next_points.push_back(Point(b_left.x() + 1, b_left.y(), b_left.z()));
            next_points.push_back(b_left);
        }
        if(coords.second == 1)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x() - 1, t_left.y(), t_left.z()));
            next_points.push_back(Point(b_left.x() - 1, b_left.y(), b_left.z()));
            next_points.push_back(b_left);
        }
    }
    if(coords.first == 'y')
    {
        if(coords.second == 0)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x(), t_left.y() + 1, t_left.z()));
            next_points.push_back(Point(b_left.x(), b_left.y() + 1, b_left.z()));
            next_points.push_back(b_left);
        }
        if(coords.second == 1)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x(), t_left.y() - 1, t_left.z()));
            next_points.push_back(Point(b_left.x(), b_left.y() - 1, b_left.z()));
            next_points.push_back(b_left);
        }
    }
    if(coords.first == 'z')
    {
        if(coords.second == 0)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x(), t_left.y(), t_left.z() + 1));
            next_points.push_back(Point(b_left.x(), b_left.y(), b_left.z() + 1));
            next_points.push_back(b_left);
        }
        if(coords.second == 1)
        {
            next_points.push_back(t_left);
            next_points.push_back(Point(t_left.x(), t_left.y(), t_left.z() - 1));
            next_points.push_back(Point(b_left.x(), b_left.y(), b_left.z() - 1));
            next_points.push_back(b_left);
        }
    }
    return Side(next_points);
}

Side Side::adjacent_left_side() const
{
    vector<Point> next_points;
    pair<char, int> coords = unchanged_coords(points_);
    Point t_right = top_left();
    Point b_right = bottom_left();

    
    if(coords.first == 'x')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x() + 1, t_right.y(), t_right.z()));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x() + 1, b_right.y(), b_right.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x() - 1, t_right.y(), t_right.z()));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x() - 1, b_right.y(), b_right.z()));
        }
    }
    if(coords.first == 'y')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x(), t_right.y() + 1, t_right.z()));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x(), b_right.y() + 1, b_right.z()));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x(), t_right.y() - 1, t_right.z()));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x(), b_right.y() - 1, b_right.z()));
        }
    }
    if(coords.first == 'z')
    {
        if(coords.second == 0)
        {
            next_points.push_back(Point(t_right.x(), t_right.y(), t_right.z() + 1));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x(), b_right.y(), b_right.z() + 1));
        }
        if(coords.second == 1)
        {
            next_points.push_back(Point(t_right.x(), t_right.y(), t_right.z() - 1));
            next_points.push_back(t_right);
            next_points.push_back(b_right);
            next_points.push_back(Point(b_right.x(), b_right.y(), b_right.z() - 1));
        }
    }
    return Side(next_points);
}