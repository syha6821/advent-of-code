#pragma once
#include "std_lib_facilities.h"
#include "branch.h"
#include <unordered_set>
#include <map>

unordered_set<Branch> remove_loser(unordered_set<Branch> branches);
unordered_set<Branch> remove_loser_(unordered_set<Branch> branches);

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


unordered_set<Branch> grow_till_the_end(const unordered_set<Branch>& branches, const unordered_set<Branch>& finished)
{
    cout << "branches : " << branches.size() << '\n';
    if (branches.size() == 0)
    {
        return finished;
    }
    else
    {
        unordered_set<Branch> next_branches;
        unordered_set<Branch> next_finished = std::move(finished);
        for(Branch branch : branches)
        {
            for(const Branch& child_branch : branch.make_child_branch())
            {
                if(child_branch.is_finished()) next_finished.insert(child_branch);
                else next_branches.insert(child_branch);
            }
        }
        return grow_till_the_end(std::move(next_branches), std::move(next_finished));
    }
}

int grow_till_the_end_(const unordered_set<Branch>& branches, int highest = 0)
{
    cout << "branches : " << branches.size() << '\n';
    if (branches.size() == 0)
    {
        return highest;
    }
    else
    {
        unordered_set<Branch> next_branches;
        for(Branch branch : branches)
        {
            for(const Branch& child_branch : branch.make_child_branch())
            {
                if(child_branch.is_finished()) 
                {
                    if(child_branch.get_total_released() > highest) highest = child_branch.get_total_released();
                }
                else next_branches.insert(child_branch);
            }
        }
        /* return grow_till_the_end_(std::move(next_branches), highest); */
        return grow_till_the_end_(std::move(remove_loser_(next_branches)), highest);
    }
}

unordered_set<Branch> remove_loser(unordered_set<Branch> branches)
{
    map<string, Branch> highest_branch_at_valve;
    for(const Branch& branch : branches)
    {
        if(highest_branch_at_valve.count(branch.get_current_valve_name()) == 1)
        {
            if (highest_branch_at_valve[branch.get_current_valve_name()].get_time() != branch.get_time())
            {
                cout << "time is different\n";
            }
            if (highest_branch_at_valve[branch.get_current_valve_name()].get_total_released() < branch.get_total_released())
            {
                highest_branch_at_valve[branch.get_current_valve_name()] = branch;
            }
        }
        else
        {
            highest_branch_at_valve.insert(make_pair(branch.get_current_valve_name(), branch));
        }
    }
    unordered_set<Branch> winners;
    for(auto branch : highest_branch_at_valve)
    {
        winners.insert(branch.second);
    }
    return winners;
}

unordered_set<Branch> remove_loser_(unordered_set<Branch> branches)
{
    map<string, vector<Branch>> highest_branch_at_valve;
    for(const Branch& branch : branches)
    {
        if(highest_branch_at_valve.count(branch.get_current_valve_name()) == 1)
        {
            if (highest_branch_at_valve[branch.get_current_valve_name()][0].get_total_released() <= branch.get_total_released())
            {
                highest_branch_at_valve[branch.get_current_valve_name()].push_back(branch);
            }
        }
        else
        {
            /* highest_branch_at_valve.insert(make_pair(branch.get_current_valve_name(), {branch})); */
            vector<Branch> new_branch;
            new_branch.push_back(branch);
            highest_branch_at_valve.insert(make_pair(branch.get_current_valve_name(), new_branch));
        }
    }
    unordered_set<Branch> winners;
    for(auto branches : highest_branch_at_valve)
    {
        for(Branch branch : branches.second)
        {
            winners.insert(branch);
        }
    }
    return winners;
}