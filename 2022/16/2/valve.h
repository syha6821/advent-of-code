#pragma once
#include "std_lib_facilities.h"

class Valve
{
public:
    Valve(string n, int f, vector<string> near):name(n), flow_rate(f), near_valves(near){};
    string get_name() const { return name; };
    int get_flow_rate() const { return flow_rate; };
    vector<string> get_near_valves_name() const { return near_valves; };
    bool is_open() { return open_; }
    int open(int passed_time)
    {
        open_ = true;
        return (26 - passed_time) * flow_rate;
    }

    bool operator<(const Valve &valve) const
    {
        return name < valve.get_name();
    }
    
    bool operator==(const Valve &valve) const
    {
        return name == valve.get_name();
    }

private:
    bool open_ = false;
    /* const string name; */
    /* const int flow_rate; */
    string name;
    int flow_rate;
    vector<string> near_valves;
};

unordered_map<string, Valve> make_valve_map(vector<Valve> valves);

vector<Valve> get_usable_valves(const vector<Valve>& valves);