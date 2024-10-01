struct Point
{
    Point(int xx, int yy):x(xx), y(yy){};
    Point(pair<int,int> xy):x(xy.first), y(xy.second){};
    int x;
    int y;

    void operator=(Point point)
    {
        x = point.x;
        y = point.y;
    }
};