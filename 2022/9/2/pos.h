#pragma once
#include "std_lib_facilities.h"

class Pos{
public:
    void R();
    void L();
    void U();
    void D();
    int get_x() const { return x; };
    int get_y() const { return y; };
    int get_shadow_x() const { return shadow_x; };
    int get_shadow_y() const { return shadow_y; };
    void follow(const Pos &H);
    void do_command(char ch);
    bool is_adjacent(const Pos& shadow);
    string hash();
    friend ostream& operator<<(ostream& stream, const Pos& p);
private:
    int x = 0, y = 0;
    int shadow_x = 0, shadow_y = 0;
};