#include "device.h"

bool is_lowest(char ch)
{
    return (ch == 'S') || (ch == 'a');
}

Map read_input(string filename)
{
    const char START = 'S';
    const char END = 'E';
    vector<vector<Area>> map;

    ifstream ifs(filename);
    string line;

    pair<int,int> start;
    pair<int,int> end;
    int y = 0;
    while(getline(ifs,line))
    {
        vector<Area> area_row;
        int x = 0;
        for(char ch : line)
        {
            if(ch == START)
            {
                start.first = x;
                start.second = y;
            }
            if(ch == END)
            {
                end.first = x;
                end.second = y;
            }
            area_row.push_back(Area(ch,Point(x,y)));
            x++;
        }
        map.push_back(area_row);
        y++;
    }
    return Map(map,Point(start),Point(end));
}

Map read_reverse_map(string filename) // only has End point
{
    const char END = 'E';
    vector<vector<Area>> map;

    ifstream ifs(filename);
    string line;
    pair<int,int> end;
    int y = 0;
    while(getline(ifs,line))
    {
        vector<Area> area_row;
        int x = 0;
        for(char ch : line)
        {
            if(ch == END)
            {
                end.first = x;
                end.second = y;
            }
            area_row.push_back(Area(ch,Point(x,y)));
            x++;
        }
        map.push_back(area_row);
        y++;
    }
    return Map(map,Point(make_pair(0,0)),Point(end));
}