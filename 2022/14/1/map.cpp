#include "map.h"

bool is_vertical_line(Point first, Point second)
{
    return first.x == second.x;
}

bool is_horizontal_line(Point first, Point second)
{
    return first.y == second.y;
}

void Map::put_rocks_line(Point first, Point second ,bool is_last)
{
    if (is_horizontal_line(first, second))
    {
        if(first.x > second.x)
        {
            for(int i = first.x; i > second.x; i--)
            {
                materials.insert(make_pair(Point(i, first.y), Material::ROCK));
            }
        }
        else
        {
            for(int i = first.x; i < second.x; i++)
            {
                materials.insert(make_pair(Point(i, first.y), Material::ROCK));
            }
        }
    }
    else if (is_vertical_line(first, second))
    {
        if(first.y > second.y)
        {
            for(int i = first.y; i > second.y; i--)
            {
                materials.insert(make_pair(Point(first.x, i), Material::ROCK));
            }
        }
        else
        {
            for(int i = first.y; i < second.y; i++)
            {
                materials.insert(make_pair(Point(first.x, i), Material::ROCK));
            }
        }
    }
    if (is_last) materials.insert(make_pair(Point(second.x, second.y), Material::ROCK));
}

void Map::put_rocks(vector<Point> points)
{
    Point first = points.back();
    Point second = points[points.size() - 2];
    if(points.size() == 2)
    {
        put_rocks_line(first,second,true);
        return;
    }
    else
    {
        put_rocks_line(first,second,false);
        points.pop_back();
        put_rocks(points);
    }
}

Map::Map(pair<vector<vector<Point>>, int> scanned):deepest(scanned.second)
{
    for(vector<Point> points : scanned.first)
    {
        put_rocks(points);
    }
};

Material Map::get_material(Point point)
{
    try
    {
        /* cout << "Get material from " << point.x << ',' << point.y << " and it is "; */
        /* Material m = materials[point]; */
        const Material m = materials.at(point);
        /* if (m == Material::ROCK) cout << "Rock\n"; */
        /* if (m == Material::AIR) cout << "Air\n"; */
        /* if (m == Material::SAND) cout << "Sand\n"; */
        return m;
    }
    catch(const std::exception& e)
    {
        /* cout << "key not found at : " << point.x << ',' << point.y << '\n'; */
        return Material::AIR;
    }
    
}

void Map::insert_material(Point point, Material material)
{
    materials.insert(make_pair(point, material));
}