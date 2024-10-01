#include "droplet.h"
#include <set>
#include <unordered_set>

Droplet::Droplet(unordered_set<Cube> cubes) : cubes_(cubes), sides_(Surface())
{
    int lowest_x = (*cubes.begin()).x();
    int highest_x = (*cubes.begin()).x();

    int lowest_y = (*cubes.begin()).y();
    int highest_y = (*cubes.begin()).y();

    int lowest_z = (*cubes.begin()).z();
    int highest_z = (*cubes.begin()).z();

    for(Cube cube : cubes_)
    {
        if (cube.x() < lowest_x) lowest_x = cube.x();
        if (cube.x() > highest_x) highest_x = cube.x();

        if (cube.y() < lowest_y) lowest_y = cube.y();
        if (cube.y() > highest_y) highest_y = cube.y();

        if (cube.z() < lowest_z) lowest_z = cube.z();
        if (cube.z() > highest_z) highest_z = cube.z();
    }
    
    max_x_ = highest_x;
    min_x_ = lowest_x;

    max_y_ = highest_y;
    min_y_ = lowest_y;

    max_z_ = highest_z;
    min_z_ = lowest_z;

    for(Cube cube : cubes_)
    {
        if(cube.y() == lowest_y)
        {
            bottom_.insert(cube);
        }
    }
};

bool Droplet::is_valid_steam(const Cube& steam)
{
    bool x_okay = (steam.x() >= min_x_ - 1) && (steam.x() <= max_x_ + 1);
    bool y_okay = (steam.y() >= min_y_ - 1) && (steam.y() <= max_x_ + 1);
    bool z_okay = (steam.z() >= min_z_ - 1) && (steam.z() <= max_z_ + 1);
    
    return x_okay && y_okay && z_okay && !used_steams_.count(steam);
}

unordered_set<Cube> Droplet::starting_steams()
{
    unordered_set<Cube> steams;
    for(Cube cube : bottom_)
    {
        steams.insert(Cube({cube.x(), cube.y() - 1, cube.z()}));
    }
    return steams;
}

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

unordered_set<Cube> Droplet::spread_steam(const Cube& cube)
{
    unordered_set<Cube> next_steams_candidates;
    next_steams_candidates.insert(Cube({cube.x()+1, cube.y(), cube.z()}));
    next_steams_candidates.insert(Cube({cube.x()-1, cube.y(), cube.z()}));

    next_steams_candidates.insert(Cube({cube.x(), cube.y()+1, cube.z()}));
    next_steams_candidates.insert(Cube({cube.x(), cube.y()-1, cube.z()}));

    next_steams_candidates.insert(Cube({cube.x(), cube.y(), cube.z()+1}));
    next_steams_candidates.insert(Cube({cube.x(), cube.y(), cube.z()-1}));

    unordered_set<Cube> next_steams;
    for(const Cube& steam : next_steams_candidates)
    {
        if(is_valid_steam(steam))
        {
            next_steams.insert(steam);
        }
    }

    return next_steams;
}

void Droplet::spreader()
{
    cout << "max x : " << max_x_ << '\n';
    cout << "max y : " << max_y_ << '\n';
    cout << "max z : " << max_z_ << '\n';
    cout << "min x : " << min_x_ << '\n';
    cout << "min y : " << min_y_ << '\n';
    cout << "min z : " << min_z_ << '\n';
    spread(starting_steams());
}

void Droplet::spread(unordered_set<Cube> current_steams)
{
    if(current_steams.size() == 0)
    {
        cout << "size zero\n";
        return;
    }
    else
    {
        for(Cube steam : current_steams)
        {
            used_steams_.insert(steam);
            for(Side steam_side : steam.sides())
            {
                if(sides_.count(steam_side))
                {
                    stepped_sides_.insert(steam_side);
                }
            }
        }
        // ! more restriction needed (like bottom limit or left limit, right limit...)
        // done ^ rules in is_valid_steam()
        
        unordered_set<Cube> next_steams;
        for(Cube steam : current_steams)
        {
            for(Cube next_steam : spread_steam(steam))
            {
                /* cout << spread_steam(steam).size() << '\n'; */
                if(not cubes_.count(next_steam) && not used_steams_.count(next_steam))
                {
                    /* cout << "passed!\n"; */
                    next_steams.insert(next_steam);
                }
            }
        }
        return spread(next_steams);
    }
}