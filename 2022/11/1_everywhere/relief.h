#pragma once
#include "std_lib_facilities.h"
#include "item.h"
#include "monkey.h"

class Relief
{
public:
    Relief(vector<pair<char, int>> o_n_list):op_num_list(o_n_list){};
    
    void operator () (Item& item)
    {
        for (pair<char, int> op_num : op_num_list)
        {
            item.set_value(calc(op_num.first, item.get_value(), op_num.second));
        }
    }
    
    void print_info()
    {
        for (auto op_num : op_num_list)
        {
            cout << op_num.first << op_num.second << ' ';
        }
        cout << '\n';
    }

private:
    vector<pair<char, int>> op_num_list;
};

const vector<char> operators = {'+','*','/','-','%'};
vector<vector<Relief>> make_relief_combination(vector<Relief> relieves, int combination_count);

vector<Relief> make_relieves(int expr_length,int end_num);