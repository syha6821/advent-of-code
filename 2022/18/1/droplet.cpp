#include "droplet.h"
#include <set>
#include <unordered_set>

unordered_set<Side> Droplet::Surface()
{
    unordered_set<Side> sides;
    for (const Cube& cube : cubes_)
    {
        for(const Side& side : std::move(cube.sides()))
        {
            if(! sides.insert(side).second) sides.erase(side);
        }
    }
    return sides;
}

bool Droplet::is_valid(Side side)
{
    if((!sides_.count(side)) || stepped_sides_.count(side))
    {
        return false;
    }
    return true;
}

void Droplet::spreader()
{
    for(Side side : sides_)
    {
        int before_size = stepped_sides_.size();
        spread({side});
        int after_size = stepped_sides_.size();

        if (before_size != after_size)
        {
            cout << "each droplet : " << (after_size - before_size) << '\n';
        }
    }
}

void Droplet::spread(unordered_set<Side> current_sides)
{
    if(current_sides.size() == 0)
    {
        return;
    }
    else
    {
        unordered_set<Side> next_sides;
        for (Side side : current_sides)
        {
            stepped_sides_.insert(side);
        }
        for(Side side : current_sides)
        {
            for(Side side_ : side.AdjacentSides())
            {
                if(is_valid(side_))
                {
                    next_sides.insert(side_);
                }
            }
        }
        return spread(next_sides);
    }
}