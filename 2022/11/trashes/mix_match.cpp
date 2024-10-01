#include "std_lib_facilities.h"

const vector<char> OPS = {'+','-','*','/','%'};
const int END = 3;
const int COMBINATION_COUNT = 3;

vector<pair<char, int>> make_list(const vector<char>& ops, int end_num);
void helper_combinations(const vector<pair<char, int>>& list, int combination_count, vector<vector<pair<char,int>>>& combinations, vector<pair<char,int>> op_num_from_top = {})
{
    if(combination_count == 1)
    {
        for(auto op_num : list)
        {
            vector<pair<char,int>> combination;
            for(auto op_num_ : op_num_from_top)
            {
                combination.push_back(op_num_);
            }
            combination.push_back(op_num);
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

vector<vector<pair<char, int>>> make_combinations(const vector<pair<char, int>>& list, int combination_count)
{
    vector<vector<pair<char, int>>> combinations;
    helper_combinations(list, combination_count, combinations);
    return combinations;
}

int main()
{
    vector<pair<char,int>> list = make_list(OPS, END);
    vector<vector<pair<char,int>>> combinations = make_combinations(list, 3);
    cout << combinations.size() << '\n';
    for (auto combination : combinations)
    {
        cout << "[ ";
        for (auto op_num : combination)
        {
            cout << op_num.first << op_num.second << ' ';
        }
        cout << ']';
        cout << '\n';
    }

    return 0;
}

vector<pair<char, int>> make_list(const vector<char>& ops, int end_num)
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