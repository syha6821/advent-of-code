#include "read.h"

vector<Valve> read_file(string filename)
{
    vector<Valve> valves;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        string name = get_name(line);
        int flow_rate = get_flow_rate(line);
        vector<string> names = get_near_valves_name(line);
        valves.push_back(Valve(name, flow_rate, names));
    }
    return valves;
}

string get_name(const string& line)
{
    return string(1,line.at(6)) + line.at(7);
}

int get_flow_rate(const string& line)
{
    int equal = line.find('=');
    string after_equal = line.substr(equal + 1);
    stringstream ss(after_equal);
    int flow_rate;
    ss >> flow_rate;
    return flow_rate;
}

vector<string> get_near_valves_name(const string& line)
{
    vector<string> names;
    string str_before_names = "valve";
    int name_start = line.find(str_before_names) + str_before_names.size();
    string names_with_comma = line.substr(name_start);
    stringstream ss(names_with_comma);
    string name;
    while(getline(ss,name, ','))
    {
        names.push_back(string(1,name.at(name.size()-2)) + name.back());
    }
    return names;
}