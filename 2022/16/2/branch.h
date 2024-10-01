#pragma once
#include "std_lib_facilities.h"
#include "valve.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <unistd.h>

class Branch
{
public:
    Branch():valve_map(Branch::default_valve_map),current_valve_name(make_pair("AA","AA"))
    {
        trace_from_last_open.first.insert(valve_map.at("AA"));
        trace_from_last_open.second.insert(valve_map.at("AA"));
        for(const Valve& valve : usable_valves)
        {
            remained_valves.push_back(valve);
        }
    };
    static const unordered_map<string, Valve> default_valve_map;
    static const vector<Valve> usable_valves;

    int count_released_valves() const { return released_valves.size(); };
    Valve &get_current_valve_first() { return valve_map.at(current_valve_name.first); };
    Valve &get_current_valve_second() { return valve_map.at(current_valve_name.second); };
    unordered_map<string, Valve> &get_valve_map() { return valve_map; };
    int get_remained_valve_count() const { return remained_valves.size(); };
    vector<Valve> get_remained_valves() { return remained_valves; };
    
    int get_highest_rate_in_remains()
    {
        int highest = remained_valves[0].get_flow_rate();
        for(const Valve& remain : remained_valves)
        {
            if (highest < remain.get_flow_rate()) highest = remain.get_flow_rate();
        }
        return highest;
    }

    bool is_worth_opening(Valve valve)
    {
        if (26 - get_time() <= 0) return true;
        if ((26 - get_time()) * valve.get_flow_rate() >= ((26 - 1 - get_time()) * get_highest_rate_in_remains())) return true;
        return false;
    }
    

    bool is_highest_in_remains(const Valve& valve)
    {
        for(const Valve& remain : remained_valves)
        {
            if (valve.get_flow_rate() < remain.get_flow_rate()) return false;
        }
        return true;
    }
    
    bool is_highest_except_elephant(const Valve& valve)
    {
        for(const Valve& remain : remained_valves)
        {
            if(remain.get_flow_rate() == get_current_valve_second().get_flow_rate()) continue;
            if (valve.get_flow_rate() < remain.get_flow_rate()) return false;
        }
        return true;
    }

    void release_first_current_valve()
    {
        int released = get_current_valve_first().open(get_time());
        released_valves.insert(get_current_valve_first());
        total_released += released;
        clear_first_trace();
        trace_from_last_open.first.insert(get_current_valve_first());
        for(int i = 0; i < remained_valves.size(); i++)
        {
            if (remained_valves[i].get_name() == get_current_valve_first().get_name())
            {
                remained_valves.erase(remained_valves.begin() + i);
                break;
            }
        }
    }

    void release_second_current_valve()
    {
        int released = get_current_valve_second().open(get_time());
        released_valves.insert(get_current_valve_second());
        total_released += released;
        clear_second_trace();
        trace_from_last_open.second.insert(get_current_valve_second());
        for(int i = 0; i < remained_valves.size(); i++)
        {
            if (remained_valves[i].get_name() == get_current_valve_second().get_name())
            {
                remained_valves.erase(remained_valves.begin() + i);
                break;
            }
        }
    }

    void add_released(int released) { total_released += released; };

    int get_time() const { return time; };

    bool is_finished() const;

    /* pair<set<Valve>,set<Valve>> &get_trace_from_last_open() { return trace_from_last_open; }; */
    pair<set<Valve>,set<Valve>> get_trace_from_last_open() const { return trace_from_last_open; };
    int get_first_trace_size() const { return trace_from_last_open.first.size(); };
    int get_second_trace_size() const { return trace_from_last_open.second.size(); };
    void clear_first_trace() { trace_from_last_open.first.clear(); };
    void clear_second_trace() { trace_from_last_open.second.clear(); };
    set<Valve> get_released_valve() const { return released_valves; };

    vector<Branch> make_child_branch();
    vector<Branch> make_child_branch_elephant();
    vector<Branch> make_double_child_branch();
    unordered_set<Branch> make_double_child_branch_set();
    
    void clear_all_traces()
    {
        trace_from_last_open.first.clear();
        trace_from_last_open.second.clear();
    }

    void first_move_to(Valve& valve)
    {
        current_valve_name.first = valve.get_name();
        trace_from_last_open.first.insert(valve);
    }

    void second_move_to(Valve& valve)
    {
        current_valve_name.second = valve.get_name();
        trace_from_last_open.second.insert(valve);
    }
    
    int get_total_released() const
    {
        return total_released;
    }
    
    pair<string,string> get_current_valve_name() const
    {
        return current_valve_name;
    }
    
    bool operator==(const Branch& branch) const;

private:
    pair<set<Valve>,set<Valve>> trace_from_last_open;
    unordered_map<string, Valve> valve_map;
    pair<string,string> current_valve_name;
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
            // symmetrically same
            return hasher(branch.get_current_valve_name().first) + hasher(branch.get_current_valve_name().second);
        }
    };
}