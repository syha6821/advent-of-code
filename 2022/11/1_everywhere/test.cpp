#include "test.h"

bool is_test_round(int round)
{
    return (round % 1000 == 0 || round == 1 || round == 20);
}

const vector<int> answer(int round)
{
    map<int, vector<int>> ans = 
    {
        {1, {2,4,3,6}},
        {20, {99,97,8,103}},
        {1000, {5204,4792,199,5192}},
        {2000, {10419,9577,392,10391}},
        {3000, {15638, 14358, 587, 15593}},
        {4000, {20858, 19138, 780, 20797}},
        {5000, {26075, 23921, 974, 26000}},
        {6000, {31294, 28702, 1165, 31204}},
        {7000, {36508, 33488, 1360, 36400}},
        {8000, {41728, 38268, 1553, 41606}},
        {9000, {46945, 43051, 1746, 46807}},
        {10000, {52166, 47830, 1938, 52013}},
    };

    return ans[round];
}

bool test(int round, vector<Monkey> monkeys)
{
    const vector<int> ans = answer(round);
    for(int i = 0; i < monkeys.size(); i++)
    {
        if (ans[i] != monkeys[i].get_score()) return false;
    }
    return true;
}