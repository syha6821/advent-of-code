#include "sensor.h"

class Contains
{
public:
    Contains(int s_x, int s_y, int u, int d, int l, int r) : sensor_x(s_x), sensor_y(s_y), up(u), down(d), left(l), right(r){};
    bool operator()(int x, int y)
    {
        int shrink = abs(sensor_y - y);
        int shrink_left = left + shrink;
        int shrink_right = right - shrink;
        bool y_okay = (up <= y) && (y <= down);
        bool x_okay = (shrink_left <= x) && (x <= shrink_right);
        return y_okay && x_okay;
    }
private:
    int sensor_x;
    int sensor_y;
    int up;
    int down;
    int right;
    int left;
};

Sensor::Sensor(int xx, int yy, Beacon bc) : x(xx), y(yy), beacon(bc)
{
    distance = abs(xx - bc.get_x()) + abs(yy - bc.get_y());
    up = yy - distance;
    down = yy + distance;
    left = xx - distance;
    right = xx + distance;
    contains = [xx = xx, yy = yy, up = up, down = down, left = left, right = right](int x, int y)
    {
        return Contains(xx,yy,up,down,left,right)(x,y);
    };
};

Sensor::Sensor(pair<int,int> xy, Beacon bc):x(xy.first),y(xy.second),beacon(bc)
{
    distance = abs(xy.first - bc.get_x()) + abs(xy.second - bc.get_y());
    up = xy.second - distance;
    down = xy.second + distance;
    left = xy.first - distance;
    right = xy.first + distance;
    contains = [xy = xy, up = up, down = down, left = left, right = right](int x, int y)
    {
        return Contains(xy.first,xy.second,up,down,left,right)(x,y);
    };
};

Range Sensor::get_range_at_y(int yy) const
{
    int shrink = abs(y - yy);
    return Range(left + shrink, right - shrink);
}