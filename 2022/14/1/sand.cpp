#include "sand.h"

void Sand::set_location(Point point)
{
    location = point;
}

char Sand::fall(Map& map)
{
    map.get_material(Point(499,9));
    map.get_material(Point(500,9));
    // A = Abyss, S = Success(just falling), R = Rest
    /* if (location.y > map.get_deepest()) */
    /* { */
    /*     return 'A'; */
    /* } */
    if(is_available_spot(below(),map))
    {
        set_location(below());
        return 'S';
    }
    else if(is_available_spot(below_left(),map))
    {
        set_location(below_left());
        return 'S';
    }
    else if(is_available_spot(below_right(),map))
    {
        set_location(below_right());
        return 'S';
    }
    else
    {
        if (location.x == 500 && location.y == 0)
        {
            cout << "stuck\n";
            return 'F';
        }
        map.insert_material(location, Material::SAND);
        return 'R';
    }
}

bool is_available_spot(Point point, Map& map)
{
    if (map.get_deepest() + 2 == point.y)
    {
        return false;
    }
    if (map.get_material(point) == Material::AIR)
    {
        return true;
    }
    return false;
}

Point Sand::below()
{
    return Point(location.x , location.y + 1);
}

Point Sand::below_left()
{
    return Point(below().x - 1 , below().y);
}

Point Sand::below_right()
{
    return Point(below().x + 1 , below().y);
}