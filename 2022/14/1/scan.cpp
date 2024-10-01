#include "scan.h"

Point read_pair(string str)
{
    pair<int,int> point;
    int comma = str.find(",");
    point.first = stoi(str.substr(0,comma));
    point.second = stoi(str.substr(comma + 1, -1));
    return Point(point);
}

string cut_front_pair(string& str)
{
    string arrow = "-> ";
    int index = str.find(arrow);
    string cut =  str.substr(0,index);
    str.erase(0, cut.size() + arrow.size());
    return cut;
}

pair<vector<Point>,int> read_path(string str)
{
    vector<Point> path;
    int deepest = 0;
    while(str.size() != 0)
    {
        string pair_str = cut_front_pair(str);
        Point point = read_pair(pair_str);
        if (point.y > deepest) deepest = point.y;
        path.push_back(point);
    }
    return make_pair(path,deepest);
}

pair<vector<vector<Point>>,int> scan_file(string filename)
{
    vector<vector<Point>> paths;
    ifstream ifs(filename);
    string line;
    int deepest = 0;
    while(getline(ifs,line))
    {
        auto path = read_path(line);
        paths.push_back(path.first);
        if (path.second > deepest) deepest = path.second;
    }
    return make_pair(paths, deepest);
}