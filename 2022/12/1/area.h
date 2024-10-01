#pragma once
#include "std_lib_facilities.h"
#include "point.h"

class Area
{
public:
    Area(char ch, Point p) : height(ch), point(p){};
    Area(char ch, Point p, bool start_flag): height(ch), point(p), start(start_flag){};
    char get_height() const 
    {
        if (height == 'S') return 'a';
        if (height == 'E') return 'z';
        return height;
    }
    Point get_point() const { return point; }
    bool is_start() { return start; };
    bool is_end(){ return height == 'E';};
    void set_start_flag(bool flag) { start = flag; };
    void check_stepped() { stepped = true; };
    bool is_stepped()
    {
        /* if (stepped) cout << "but already stepped\n"; */
        return stepped;
    };
    void reset_stepped()
    {
        stepped = false;
    }

private:
    bool start = false;
    const char height;
    const Point point;
    bool stepped = false;
};