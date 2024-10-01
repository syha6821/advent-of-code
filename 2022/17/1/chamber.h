#pragma once
#include "std_lib_facilities.h"
#include <bitset>
#include "jet.h"

class Chamber
{
public:
    static const unsigned int WIDTH = 7;
    static const unsigned int UP_PAD = 3;

    using SLICE = bitset<WIDTH>;
    using WINDOW = vector<SLICE>;

    Chamber()
    {
        SLICE ground = SLICE(0).flip();
        rock_stacks_.push_back(ground);
        AddAirAboveStack(UP_PAD);
    };
    WINDOW window(int height, int y);
    void replace(int height, int y, WINDOW window);
    void AddAirAboveStack(int air);
    int height() { return rock_stacks_.size(); };
    void cleanAir();
    SLICE top();
    SLICE bottom() { return rock_stacks_[0]; };
    SLICE SliceAtFromTop(int num) { return rock_stacks_[rock_stacks_.size() - 1 - num];};
    SLICE SliceAt(int num) { return rock_stacks_[num];};

    friend ostream &operator<<(ostream &stream, const Chamber &chamber);

private:
    vector<SLICE> rock_stacks_;
};
