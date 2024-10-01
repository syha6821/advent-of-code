#include "std_lib_facilities.h"

const bool VISIBLE = true;
vector<vector<int>> rotate_left(const vector<vector<int>>& v);
vector<vector<int>> rotate_right(const vector<vector<int>>& v);

int main()
{
    vector<vector<int>> e;
    e.push_back({3,0,3,7,3});
    e.push_back({2,5,5,1,2});
    e.push_back({6,5,3,3,2});
    e.push_back({3,5,3,9,0});
    
    for(auto row : e)
    {
        for (auto i : row)
        {
            cout << i << ' ';
        }
        cout << '\n';
    }
    
    cout << "left\n";

    for(auto row : rotate_left(e))
    {
        for (auto i : row)
        {
            cout << i << ' ';
        }
        cout << '\n';
    }

    cout << "right\n";

    for(auto row : rotate_right(e))
    {
        for (auto i : row)
        {
            cout << i << ' ';
        }
        cout << '\n';
    }

    cout << "origin\n";

    for(auto row : rotate_right(rotate_left(e)))
    {
        for (auto i : row)
        {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

vector<vector<int>> rotate_left(const vector<vector<int>>& v)
{
    vector<vector<int>> rotated;
    for(int i = v[0].size() - 1; i >= 0; i--)
    {
        vector<int> line;
        for(int j  = 0; j < v.size(); j++)
        {
            line.push_back(v[j][i]);
        }
        rotated.push_back(line);
    }
    return rotated;
}

vector<vector<int>> rotate_right(const vector<vector<int>>& v)
{
    vector<vector<int>> rotated;
    for(int i = 0; i < v[0].size(); i++)
    {
        vector<int> line;
        for(int j  = v.size() - 1; j >= 0; j--)
        {
            line.push_back(v[j][i]);
        }
        rotated.push_back(line);
    }
    return rotated;
}