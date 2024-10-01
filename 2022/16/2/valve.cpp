#include "valve.h"
#include <unordered_map>

unordered_map<string, Valve> make_valve_map(vector<Valve> valves)
{
    unordered_map<string, Valve> valve_map;
    for(Valve valve: valves)
    {
        valve_map.insert(make_pair(valve.get_name(), valve));
    }
    return valve_map;
}

vector<Valve> get_usable_valves(const vector<Valve>& valves)
{
    vector<Valve> usable;
    for(const Valve& valve : valves)
    {
        if (valve.get_flow_rate() != 0) usable.push_back(valve);
    }
    return usable;
}