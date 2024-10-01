#include "mix_match.h"

void helper_combinations(const vector<pair<char,int>>& list, int combination_count, vector<vector<Relief>>& combinations, vector<pair<char,int>> op_num_from_top = {})
{
    if(combination_count == 1)
    {
        for(auto op_num : list)
        {
            vector<Relief> combination;
            int relief_count = 0;
            for(auto op_num_ : op_num_from_top)
            {
                combination.push_back(Relief(op_num_.first, op_num_.second, relief_count));
                relief_count++;
            }
            combination.push_back(Relief(op_num.first, op_num.second, relief_count));
            combinations.push_back(combination);
        }
    }

    else
    {
        for(auto op_num : list)
        {
            vector<pair<char,int>> op_nums = op_num_from_top;
            op_nums.push_back(op_num);
            helper_combinations(list, combination_count-1, combinations, op_nums);
        }
    }
}

vector<vector<Relief>> make_combinations(const vector<pair<char,int>>& list, int combination_count)
{
    vector<vector<Relief>> combinations;
    helper_combinations(list, combination_count, combinations);
    return combinations;
}

vector<pair<char,int>> make_list(const vector<char>& ops, int end_num)
{
    vector<pair<char, int>> list;
    for (int i = 1; i <= end_num; i++)
    {
        for (char op : ops)
        {
            list.push_back(make_pair(op, i));
        }
    }
    return list;
}