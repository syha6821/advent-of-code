#include "branch.h"
bool Branch::is_finished() const
{
    return (time == 30 || released_valves.size() == usable_valves.size());
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

        //Make possible child branches

        // open valve situation in current valve
        if(get_current_valve().get_flow_rate() != 0 && !get_current_valve().is_open())
        {
            // If its valve is highest in the remains, then open and finish Because there could be no better branches than this.
            if (is_highest_in_remains(get_current_valve()))
            {
                Branch branch = *this;
                branch.release_current_valve();
                return {branch};
            }
            Branch branch = *this;
            branch.release_current_valve();
            next_branches.push_back(branch);
        }
        
        // move to next valves
        for(string branch_name : this->get_current_valve().get_near_valves_name())
        {
            Valve& valve = this->get_valve_map().at(branch_name);
            // If it looks like spinning then stop this branch
            if (this->get_trace_from_last_open().count(valve) == 1)
            {
                continue;
            }
            else
            {
                Branch branch = *this;
                branch.move_to(valve);
                next_branches.push_back(branch);
            }
        }
        return next_branches;
    }
}

vector<Branch> Branch::make_child_branch_with_elephant()
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

        //Make possible child branches

        // open valve situation in current valve
        if(get_current_valve().get_flow_rate() != 0 && !get_current_valve().is_open())
        {
            // If its valve is highest in the remains, then open and finish Because there could be no better branches than this.
            if (is_highest_in_remains(get_current_valve()))
            {
                Branch branch = *this;
                branch.release_current_valve();
                return {branch};
            }
            Branch branch = *this;
            branch.release_current_valve();
            next_branches.push_back(branch);
        }
        
        // move to next valves
        for(string branch_name : this->get_current_valve().get_near_valves_name())
        {
            Valve& valve = this->get_valve_map().at(branch_name);
            // If it looks like spinning then stop this branch
            if (this->get_trace_from_last_open().count(valve) == 1)
            {
                continue;
            }
            else
            {
                Branch branch = *this;
                branch.move_to(valve);
                next_branches.push_back(branch);
            }
        }
        return next_branches;
    }
}