#pragma once
#include "std_lib_facilities.h"
#include <queue>

class Pos{
public:
    void R();
    void L();
    void U();
    void D();
    int get_x() const { return x; };
    int get_y() const { return y; };
    void follow(const Pos &H);
    void do_command(char ch);
    bool is_adjacent(const Pos& head);
    int distance_from(const Pos& head);
    string hash();
    friend ostream& operator<<(ostream& stream, const Pos& p);
private:
    int x = 0, y = 0;
};