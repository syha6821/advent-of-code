#pragma once
#include "std_lib_facilities.h"
#include <bitset>
#include "chamber.h"
#include "jet.h"

class Rock
{
public:
    const static int LEFT_PAD = 2;
    using SLICE = bitset<Chamber::WIDTH>;
    using SPRITE = vector<bitset<Chamber::WIDTH>>;

    void Move(Jet jet, const Chamber::WINDOW& window);
    Rock(SPRITE sprite):sprite_(sprite){};
    bool Fall(const Chamber::WINDOW& target);
    int height() { return sprite_.size(); };
    Chamber::WINDOW overlapped(const Chamber::WINDOW& window);

    friend ostream &operator<<(ostream &stream, const Rock &rock);

private:
    SPRITE MovedSprite(Jet jet);
    SPRITE sprite_;
};