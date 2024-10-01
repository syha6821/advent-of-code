#include "chamber.h"

Chamber::WINDOW Chamber::window(int height, int y)
{
    WINDOW window;
    for (int i = height - y; i < height; i++)
    {
        window.push_back(rock_stacks_[i]);
    }
    return window;
}

void Chamber::AddAirAboveStack(int air)
{
    for(int i = 0; i < air; i++)
    {
        rock_stacks_.push_back(SLICE(0));
    }
}
void Chamber::replace(int height, int y, WINDOW window)
{
    for (int i = height - y, j = 0; i < height; i++, j++)
    {
        rock_stacks_[i] = window[j];
    }
}

ostream &operator<<(ostream &stream, const Chamber &chamber)
{
    for(int i = chamber.rock_stacks_.size() - 1; i >=0; i--)
    {
        Chamber::SLICE slice = chamber.rock_stacks_[i];
        for (int j = slice.size() - 1; j >= 0 ; j--)
        {
            if (slice[j] == 1)
            {
                stream << "⬛ ";
            }
            else if (slice[j] == 0)
            {
                stream << "⬜ ";
            }
        }
        stream << '\n';
    }
    return stream;
}

void Chamber::cleanAir()
{
    while(rock_stacks_.back() == 0)
    {
        rock_stacks_.pop_back();
    }
}

Chamber::SLICE Chamber::top()
{
    int count = 0;
    int back = rock_stacks_.size() - 1;
    while(rock_stacks_[back] == 0)
    {
        count++;
        back--;
    }
    return rock_stacks_[rock_stacks_.size() - 1 - count];
}