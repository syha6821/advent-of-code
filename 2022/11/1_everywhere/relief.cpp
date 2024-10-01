#include "relief.h"

vector<pair<char,int>> op_num_list(const vector<char>& ops, int end_num)
{
    vector<pair<char, int>> list;
    for (int i = 0; i <= end_num; i++)
    {
        for (char op : ops)
        {
            list.push_back(make_pair(op, i));
        }
    }
    return list;
}

void helper_combinations(const vector<pair<char,int>>& op_num_list, int combination_length, vector<vector<pair<char,int>>>& combinations, vector<pair<char,int>> op_num_from_top = {})
{
    if(combination_length == 1)
    {
        for(auto op_num : op_num_list)
        {
            vector<pair<char,int>> combination;
            for(auto op_num_ : op_num_from_top)
            {
                combination.push_back(make_pair(op_num_.first, op_num_.second));
            }
            combination.push_back(make_pair(op_num.first, op_num.second));
            combinations.push_back(combination);
        }
    }

    else
    {
        for(auto op_num : op_num_list)
        {
            vector<pair<char,int>> op_nums = op_num_from_top;
            op_nums.push_back(op_num);
            helper_combinations(op_num_list, combination_length - 1, combinations, op_nums);
        }
    }
}

vector<vector<pair<char, int>>> op_num_combinations(const vector<pair<char,int>>& op_num_list, int combination_length)
{
    vector<vector<pair<char, int>>> combinations;
    helper_combinations(op_num_list, combination_length, combinations);
    return combinations;
}

vector<Relief> make_relieves(int expr_length,int end_num)
{
    vector<Relief> relieves;
    auto op_num_list_ = op_num_list(operators, end_num);
    auto combinations = op_num_combinations(op_num_list_, expr_length);
    for (auto combination : combinations)
    {
        relieves.push_back(Relief(combination));
    }
    return relieves;
}

void helper_relief_combinations(const vector<Relief>& relieves, int combination_count, vector<vector<Relief>>& combinations, vector<Relief> relief_from_top = {})
{
    if(combination_count == 1)
    {
        for(Relief relief : relieves)
        {
            vector<Relief> combination;
            for(Relief relief_ : relief_from_top)
            {
                combination.push_back(relief_);
            }
            combination.push_back(relief);
            combinations.push_back(combination);
        }
    }

    else
    {
        for(auto relief : relieves)
        {
            vector<Relief> relieves_ = relief_from_top;
            relieves_.push_back(relief);
            helper_relief_combinations(relieves, combination_count - 1, combinations, relieves_);
        }
    }
}

vector<vector<Relief>> make_relief_combination(vector<Relief> relieves, int combination_count)
{
    vector<vector<Relief>> combinations;
    helper_relief_combinations(relieves, combination_count, combinations);
    return combinations;
}