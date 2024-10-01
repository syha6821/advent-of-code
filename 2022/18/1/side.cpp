#include "side.h"

Point Side::center()
{
    int x_sum = 0;
    int y_sum = 0;
    int z_sum = 0;
    for(Point point : points_)
    {
        x_sum += point.x();
        y_sum += point.y();
        z_sum += point.z();
    }
    return Point({x_sum / 4, y_sum / 4, z_sum / 4});
}

ostream &operator<<(ostream &stream, const Side &side)
{
    stream << '[';
    for(Point point : side.points())
    {
        stream << point << ',';
    }
    stream << ']';

    return stream;
};

vector<set<Point>> Side::make_lines()
{
    Point first = *points_.begin();
    Point second = *(next(points_.begin(),1));
    Point third = *(next(points_.begin(),2));
    Point fourth = *(next(points_.begin(),3));

    vector<set<Point>> line_list;
    line_list.push_back({first,second});
    line_list.push_back({first,third});
    line_list.push_back({second,fourth});
    line_list.push_back({third,fourth});
    
    return line_list;
}

vector<Side> Side::AdjacentSides()
{
    vector<Side> adjacent_sides;
    vector<Side> temp_sides;

    for(set<Point> points : lines_)
    {
        Point first = *points.begin();
        Point second = *(next(points.begin(), 1));
        if(first.x() != second.x())
        {
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(i != j && (i == 0 || j == 0))
                    {
                        Side side = Side({first,second,Point({first.x(),first.y()+i, first.z()+j}),Point({second.x(),second.y()+i, second.z()+j})});
                        if (this->points() != side.points())
                        {
                            adjacent_sides.push_back(side);
                        }
                    }
                }
            }
        }
        else if(first.y() != second.y())
        {
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(i != j && (i == 0 || j == 0))
                    {
                        Side side = Side({first,second,Point({first.x()+i,first.y(), first.z()+j}),Point({second.x()+i,second.y(), second.z()+j})});
                        if (this->points() != side.points())
                        {
                            adjacent_sides.push_back(side);
                        }
                    }
                }
            }
        }
        else if(first.z() != second.z())
        {
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(i != j && (i == 0 || j == 0))
                    {
                        Side side = Side({first,second,Point({first.x()+j,first.y()+i, first.z()}),Point({second.x()+j,second.y()+i, second.z()})});
                        if (this->points() != side.points())
                        {
                            adjacent_sides.push_back(side);
                        }
                    }
                }
            }
        }
    }
    return adjacent_sides;
}