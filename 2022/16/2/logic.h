#pragma once
#include "std_lib_facilities.h"
#include "branch.h"
#include <unordered_set>
#include <map>

unordered_set<Branch> remove_loser_hash(unordered_set<Branch> branches);
unordered_set<Branch> remove_loser_from_compare_to_highest(unordered_set<Branch> branches, int highest);
unordered_set<Branch> remove_same_open_but_lower_loser(unordered_set<Branch> branches);

int get_high_score(const unordered_set<Branch>& branches)
{
    int highest = 0;
    for(const Branch branch : branches)
    {
        if(branch.get_total_released() > highest) highest = branch.get_total_released();
    }
    return highest;
}

bool is_all_finished(const unordered_set<Branch>& branches)
{
    for(const Branch& branch : branches)
    {
        if (!branch.is_finished()) return false;
    }
    return true;
}


int grow_till_the_end_(const unordered_set<Branch>& branches, int highest = 0)
{
    cout << "branches : " << branches.size() << '\n';
    /* for(const Branch& branch : branches) */
    /* { */
    /*     cout << '('<< branch.get_current_valve_name().first << ',' << branch.get_current_valve_name().second << ':' << branch.get_total_released() << ") "; */
    /* } */
    /* cout << '\n'; */
    if (branches.size() == 0)
    {
        return highest;
    }
    else
    {
        unordered_set<Branch> next_branches;
        for(Branch branch : branches)
        {
            for(const Branch& child_branch : branch.make_double_child_branch())
            {
                if(child_branch.is_finished()) 
                {
                    if(child_branch.get_total_released() > highest) highest = child_branch.get_total_released();
                }
                else next_branches.insert(child_branch);
            }
        }
        
        // should be higher than 2096
        
        // 1989 ( when remove loser hash does not care equality of the release valves )
        /* auto filtered = remove_loser_hash(remove_same_open_but_lower_loser(next_branches)); */
        /* filtered = remove_loser_from_compare_to_highest(filtered,highest); */
        
        // 2039 ( when remove loser hash does not care equality of the release valves )
        //! but became 2304 with open state
        auto filtered = remove_loser_hash(remove_loser_from_compare_to_highest(next_branches,highest));
        filtered = remove_same_open_but_lower_loser(filtered);

        // 1941 ( when remove loser hash does not care equality of the release valves )
        /* auto filtered = remove_loser_hash(remove_loser_from_compare_to_highest(next_branches,highest)); */

        // 2039 ( when remove loser hash does not care equality of the release valves )
        /* auto filtered = remove_loser_hash(next_branches); */
        /* filtered = remove_same_open_but_lower_loser(filtered); */

        //! 1941 2304
        /* auto filtered = remove_loser_hash(next_branches); */

        /* filtered = remove_loser_from_compare_to_highest(filtered,highest); */

        // too slow
        /* auto filtered = remove_loser_from_compare_to_highest(next_branches,highest); */
        /* filtered = remove_same_open_but_lower_loser(filtered); */
        

        // 1989 ( When remove loser hash does not care equality of the release valves )
        /* auto filtered = remove_same_open_but_lower_loser(remove_loser_from_compare_to_highest(next_branches,highest)); */
        /* filtered = remove_loser_hash(filtered); */
            
        return grow_till_the_end_(filtered, highest);
    }
}

vector<Valve> sorted_valves(vector<Valve> valves)
{
    int count = 0;
    while(count != 0)
    {
        count = 0;
        for (int i = 1; i < valves.size(); i++)
        {
            if(valves[i].get_flow_rate() > valves[i-1].get_flow_rate())
            {
                count++;
                swap(valves[i],valves[i-1]);
            }
        }
    }
    return valves;
}

int optimistic_possible_rest_point(Branch branch)
{
    int total_time = 26;
    int passed_time = branch.get_time();
    int sum = 0;
    int count = 1;
    for(Valve valve : sorted_valves(branch.get_remained_valves()))
    {
        if(total_time -  passed_time <= 0) return sum;
        sum += (total_time - passed_time) * valve.get_flow_rate();
        if (count % 2 == 0) passed_time++;
        count++;
    }
    return sum;
}

unordered_set<Branch> remove_loser_from_compare_to_highest(unordered_set<Branch> branches, int highest)
{
    unordered_set<Branch> after_removed;
    for (Branch branch : branches)
    {
        if(optimistic_possible_rest_point(branch) + branch.get_total_released() > highest)
        {
            after_removed.insert(branch);
        }
    }
    return after_removed;
}

unordered_set<Branch> remove_same_open_but_lower_loser(unordered_set<Branch> branches)
{
    map<size_t, vector<Branch>> winners;
    hash<string> str_hasher;
    for(Branch branch : branches)
    {
        size_t hashed = 0;

        for(const Valve& valve : branch.get_released_valve())
        {
            hashed += str_hasher(valve.get_name());
        }

        if(winners.count(hashed) == 1)
        {
            // released more
            if (winners[hashed][0].get_total_released() == branch.get_total_released())
            {
                winners[hashed].push_back(branch);
            }
            else if (winners[hashed][0].get_total_released() < branch.get_total_released())
            {
                winners[hashed].clear();
                winners[hashed].push_back(branch);
            }
        }
        else
        {
            vector<Branch> new_branch;
            new_branch.push_back(branch);
            winners.insert(make_pair(hashed,new_branch));
        }
    }
    unordered_set<Branch> result;
    for(auto winner : winners)
    {
        for(const Branch& branch : winner.second)
        {
            result.insert(branch);
        }
    }
    return result;
}

unordered_set<Branch> remove_loser_hash(unordered_set<Branch> branches)
{
    /* hash<Branch> hasher; */
    map<size_t, vector<Branch>> winners;
    /* map<set<string>, vector<Branch>> winners; */
    hash<string> str_hasher;
    /* map<string, vector<Branch>> winners; */
    for(Branch branch : branches)
    {
        /* auto hashed = hasher(branch); */
        
        // this is 2096
        /* auto hashed = str_hasher(branch.get_current_valve_name().first + branch.get_current_valve_name().second); */

        
        // this is 1941
        /* auto hashed = str_hasher(branch.get_current_valve_name().first) + str_hasher(branch.get_current_valve_name().second); */

        //? this is same as above but with valve open state
        auto hashed = str_hasher(branch.get_current_valve_name().first + to_string(branch.get_current_valve_first().is_open())) + str_hasher(branch.get_current_valve_name().second + to_string(branch.get_current_valve_second().is_open()));
        
        // this is 1941
        /* set<string> hashed; */
        /* hashed.insert(branch.get_current_valve_name().first); */
        /* hashed.insert(branch.get_current_valve_name().second); */
        
        // this is 2096 and many opened. and this does not treat symmetric as same.
        /* string hashed = branch.get_current_valve_name().first +  branch.get_current_valve_name().second; */

        //! added checking open or not
        /* string hashed = branch.get_current_valve_name().first +  branch.get_current_valve_name().second + to_string(branch.get_current_valve_first().is_open()) + to_string(branch.get_current_valve_second().is_open()); */

        // Takes so long and 1992 why...
        /* string hashed = branch.get_current_valve_name().first +  branch.get_current_valve_name().second + to_string(branch.get_remained_valve_count()); */

        if(winners.count(hashed) == 1)
        {
            // released more
            if (winners[hashed][0].get_total_released() == branch.get_total_released())
            {
                winners[hashed].push_back(branch);
            }
            else if (winners[hashed][0].get_total_released() < branch.get_total_released())
            {
                winners[hashed].clear();
                winners[hashed].push_back(branch);
            }
        }
        else
        {
            vector<Branch> new_branch;
            new_branch.push_back(branch);
            winners.insert(make_pair(hashed,new_branch));
        }
    }
    unordered_set<Branch> result;
    for(auto winner : winners)
    {
        for(const Branch& branch : winner.second)
        {
            result.insert(branch);
        }
    }
    return result;
}