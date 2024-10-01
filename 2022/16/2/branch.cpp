#include "branch.h"

bool Branch::is_finished() const
{
    if (time == 26 && released_valves.size() >= 13)
    {
        cout << "opened : " << released_valves.size()  << '/' << usable_valves.size() << ':' << total_released << '\n';
    }
    if (released_valves.size() == usable_valves.size())
    {
        cout << "opened all\n";
    }
    return (time == 26 || released_valves.size() == usable_valves.size());
}

vector<Branch> Branch::make_child_branch()
{
    if(is_finished())
    {
        Branch branch = *this;
        return {branch};
    }
    else
    {
        time++;
        vector<Branch> next_branches;

        // open valve situation in current valve
        if(get_current_valve_first().get_flow_rate() != 0 && !get_current_valve_first().is_open())
        {
            // If its valve is highest in the remains, then open and finish Because there could be no better branches than this.
            /* if (is_highest_in_remains(get_current_valve_first())) */
            /* if (is_worth_opening(get_current_valve_first()) || is_highest_except_elephant(get_current_valve_first())) */
            /* if (is_worth_opening(get_current_valve_first())) */
            /* { */
            /*     Branch branch = *this; */
            /*     branch.release_first_current_valve(); */
            /*     return {branch}; */
            /* } */
            Branch branch = *this;
            branch.release_first_current_valve();
            next_branches.push_back(branch);
        }
        
        // move to next valves
        for(string valve_name : this->get_current_valve_first().get_near_valves_name())
        {
            Valve& valve = this->get_valve_map().at(valve_name);
            // If it looks like spinning then stop this branch
            /* if (this->get_trace_from_last_open().first.count(valve) == 1) */
            /* { */
            /*     continue; */
            /* } */
            /* else */
            {
                Branch branch = *this;
                branch.first_move_to(valve);
                next_branches.push_back(branch);
            }
        }
        return next_branches;
    }
}

vector<Branch> Branch::make_child_branch_elephant()
{
    if(released_valves.size() == usable_valves.size())
    {
        Branch branch = *this;
        return {branch};
    }
    else
    {
        vector<Branch> next_branches;

        // open valve situation in current valve
        if(get_current_valve_second().get_flow_rate() != 0 && !get_current_valve_second().is_open())
        {
            // If its valve is highest in the remains, then open and finish Because there could be no better branches than this.
            /* if (is_highest_in_remains(get_current_valve_second())) */
            /* if (is_worth_opening(get_current_valve_second())) */
            /* { */
            /*     Branch branch = *this; */
            /*     branch.release_second_current_valve(); */
            /*     return {branch}; */
            /* } */
            Branch branch = *this;
            branch.release_second_current_valve();
            next_branches.push_back(branch);
        }
        
        // move to next valves
        for(string valve_name : this->get_current_valve_second().get_near_valves_name())
        {
            Valve& valve = this->get_valve_map().at(valve_name);
            // If it looks like spinning then stop this branch
            if (this->get_trace_from_last_open().second.count(valve) == 1)
            {
                continue;
            }
            else
            {
                Branch branch = *this;
                branch.second_move_to(valve);
                next_branches.push_back(branch);
            }
        }
        return next_branches;
    }
}

vector<Branch> Branch::make_double_child_branch()
{
    vector<Branch> first_child = make_child_branch();
    vector<Branch> second_child;
    for(Branch branch : first_child)
    {
        vector<Branch> branches_ = branch.make_child_branch_elephant();
        for(Branch branch_ : branches_)
        {
            second_child.push_back(branch_);
        }
    }
    return second_child;
}

unordered_set<Branch> Branch::make_double_child_branch_set()
{
    /* cout << "make child branch.. ->"; */
    vector<Branch> first_child = make_child_branch();
    unordered_set<Branch> second_child;
    for(Branch branch : first_child)
    {
        vector<Branch> branches_ = branch.make_child_branch_elephant();
        for(Branch branch_ : branches_)
        {
            second_child.insert(branch_);
        }
    }
    return second_child;
}

bool is_symmetric(pair<string,string> p1, pair<string,string> p2)
{
    return (p1.first == p2.first && p1.second == p2.second) || (p1.first == p2.second && p1.second == p2.first);
}

bool Branch::operator==(const Branch &branch) const
{
    hash<Branch> hasher;
    // Because valves would have opened in different steps -> they are logically different

    // hasher didn't seem to work like I expected
    /* return (hasher(*this) == hasher(branch)) && (get_released_valve() == branch.get_released_valve()) && (get_total_released() == branch.get_total_released()); */

    // 2096
    return (is_symmetric(get_current_valve_name(), branch.get_current_valve_name())) && (get_released_valve() == branch.get_released_valve()) && (get_total_released() == branch.get_total_released());

    //? or should I tread symmetric branches not the same?
    // 1941 ;;
    /* return ((get_current_valve_name() == branch.get_current_valve_name())) && (get_released_valve() == branch.get_released_valve()) && (get_total_released() == branch.get_total_released()); */

    // 2096
    /* return (is_symmetric(get_current_valve_name(), branch.get_current_valve_name())) && (get_released_valve() == branch.get_released_valve()); */

    // even this results 1941
    /* return (hasher(*this) == hasher(branch)) && (get_released_valve() == branch.get_released_valve()) && (get_total_released() == branch.get_total_released() && (get_trace_from_last_open() == branch.get_trace_from_last_open())); */
}