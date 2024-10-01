#pragma once
#include "std_lib_facilities.h"
#include "valve.h"
#include <unordered_map>
#include <set>

class Branch
{
public:
    Branch():valve_map(Branch::default_valve_map),current_valve_name("AA")
    {
        trace_from_last_open.insert(valve_map.at("AA"));
        for(const Valve& valve : usable_valves)
        {
            remained_valves.push_back(valve);
        }
    };
    static const unordered_map<string, Valve> default_valve_map;
    static const vector<Valve> usable_valves;

    int count_released_valves() { return released_valves.size(); };
    Valve &get_current_valve() { return valve_map.at(current_valve_name); };
    unordered_map<string, Valve> &get_valve_map() { return valve_map; };
    
    bool is_highest_in_remains(const Valve& valve)
    {
        for(const Valve& remain : remained_valves)
        {
            if (valve.get_flow_rate() < remain.get_flow_rate()) return false;
        }
        return true;
    }

    void release_current_valve()
    {
        int released = get_current_valve().open(get_time());
        released_valves.insert(get_current_valve());
        total_released += released;
        clear_trace();
        trace_from_last_open.insert(get_current_valve());
        for(int i = 0; i < remained_valves.size(); i++)
        {
            if (remained_valves[i].get_name() == get_current_valve().get_name())
            {
                remained_valves.erase(remained_valves.begin() + i);
                break;
            }
        }
    }

    void add_released(int released) { total_released += released; };

    int get_time() const { return time; };

    bool is_finished() const;

    set<Valve> &get_trace_from_last_open() { return trace_from_last_open; };
    int get_trace_size() const { return trace_from_last_open.size(); };
    void clear_trace() {trace_from_last_open.clear();};

    vector<Branch> make_child_branch();
    vector<Branch> make_child_branch_with_elephant();
    
    void move_to(Valve& valve)
    {
        current_valve_name = valve.get_name();
        trace_from_last_open.insert(valve);
    }
    
    int get_total_released() const
    {
        return total_released;
    }
    
    string get_current_valve_name() const
    {
        return current_valve_name;
    }

    bool operator==(const Branch& branch) const
    {
        //fastest
        return (current_valve_name == branch.get_current_valve_name()) 
        && (total_released == branch.get_total_released());
    }

    bool operator<(const Branch& branch) const
    {
        //Why are resulted they different
        return (current_valve_name < branch.get_current_valve_name()) 
        || (trace_from_last_open.size() < branch.get_trace_size()) 
        || (total_released < branch.get_total_released());

        /* return (current_valve_name > branch.get_current_valve_name()) */ 
        /* || (trace_from_last_open.size() > branch.get_trace_size()) */ 
        /* || (total_released > branch.get_total_released()); */
    }

private:
    set<Valve> trace_from_last_open;
    unordered_map<string, Valve> valve_map;
    string current_valve_name;
    int time = 0;
    int total_released = 0;
    set<Valve> released_valves;
    vector<Valve> remained_valves;
    bool finished = false;
};

namespace std
{
    template<>
    struct hash<Branch>
    {
        hash<string> hasher;
        size_t operator() (const Branch& branch) const noexcept
        {
            return hasher(branch.get_current_valve_name());
        }
    };
}