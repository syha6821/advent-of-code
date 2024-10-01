#pragma once
#include "material.h"
#include "point.h"
/* #include <map> */
#include <unordered_map>

class Map
{
public:
    Map(pair<vector<vector<Point>>,int> scanned);
    Material get_material(Point point);
    void insert_material(Point, Material);
    int get_deepest() { return deepest; };
    void print_keys()
    {
        for(auto p : materials)
        {
            cout << p.first.x << ',' << p.first.y;
            if (p.second == Material::ROCK) cout << " : ROCK\n";
            if (p.second == Material::SAND) cout << " : SAND\n";
            if (p.second == Material::AIR) cout << " : AIR\n";
        }
    }

private:
    void put_rocks(vector<Point> points);
    void put_rocks_line(Point first, Point second, bool is_last);
    /* map<Point, Material> materials; */
    unordered_map<Point, Material> materials;
    int deepest = 0;
};