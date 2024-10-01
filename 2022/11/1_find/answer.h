#include <map>
#include <queue>
using namespace std;

queue<int> round_to_compare({1,20,1000,2000});

map<int, vector<int>> answer = {
    {1,{2,4,3,6}},
    {20,{99,97,8,103}},
    {1000,{5204,4792,199,5192}},
    {2000,{10419,9577,392,10391}},
};

bool check(vector<int> result, map<int,vector<int>> answer, int round)
{
    if (result == answer.at(round))
    {
        return true;
    }
    return false;
}
