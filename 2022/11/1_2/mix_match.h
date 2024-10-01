#include "std_lib_facilities.h"
#include "worry.h"

vector<pair<char,int>> make_list(const vector<char>& ops, int end_num);
void helper_combinations(const vector<pair<char,int>>& list, int combination_count, vector<vector<Relief>>& combinations, vector<pair<char,int>> op_num_from_top);
vector<vector<Relief>> make_combinations(const vector<pair<char,int>>& list, int combination_count);