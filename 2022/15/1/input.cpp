#include "input.h"

vector<Sensor> read_file(string filename)
{
    vector<Sensor> sensors;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        int colon = line.find(':');
        string sensor_info = line.substr(0,colon);
        pair<int, int> sensor_location = read_xy(sensor_info);
        string beacon_info = line.substr(colon);
        pair<int, int> beacon_location = read_xy(beacon_info);
        sensors.push_back(Sensor(sensor_location, Beacon(beacon_location)));
    }
    return sensors;
}

pair<int, int> read_xy(string line)
{
    stringstream ss(line);
    string info;
    getline(ss, info, '=');

    getline(ss, info, '=');
    int x;
    stringstream(info) >> x;

    getline(ss, info, '=');
    int y;
    stringstream(info) >> y;

    return make_pair(x,y);
}