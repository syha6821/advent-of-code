#include "std_lib_facilities.h"
#include <fstream>

struct Tree {
    bool visible;
};

enum class direction{
    LEFT,UP,RIGHT,DOWN,
};
const bool VISIBLE = true;
const direction LEFT = direction::LEFT;
const direction RIGHT = direction::RIGHT;
const direction UP = direction::UP;
const direction DOWN = direction::DOWN;
const int ASCII_FOR_NUM = 48;
const string SAMPLE = "input.txt";

vector<Tree> scan_line(vector<int> line, const direction& viewer);
vector<vector<Tree>> make_map(vector<vector<int>>& square, const direction& viewer);
vector<vector<Tree>> wrap_map(const vector<vector<Tree>>&, const vector<vector<Tree>>&);
vector<vector<Tree>> wrap_map(const vector<vector<Tree>>&, const vector<vector<Tree>>&,const vector<vector<Tree>>&, const vector<vector<Tree>>&);
vector<int> read_line(string line);
vector<vector<int>> read_square(string file_name);
vector<vector<int>> rotate_left(const vector<vector<int>>& v);
vector<vector<int>> rotate_right(const vector<vector<int>>& v);
vector<vector<Tree>> rotate_left(const vector<vector<Tree>>& v);
vector<vector<Tree>> rotate_right(const vector<vector<Tree>>& v);
int count_visible(vector<vector<Tree>> tree_map);

int main()
{
    auto square = read_square(SAMPLE);
    const auto left_map = make_map(square, LEFT);
    const auto right_map = make_map(square, RIGHT);
    const auto up_map = make_map(square, UP);
    const auto down_map = make_map(square, DOWN);
    
    cout << count_visible(wrap_map(left_map, right_map, up_map, down_map)) << '\n';

    return 0;
}

int count_visible(vector<vector<Tree>> tree_map)
{
    int count = 0;
    for(auto line  : tree_map)
    {
        for(auto tree : line)
        {
            if (tree.visible) count++;
        }
    }
    return count;
}

vector<vector<Tree>> wrap_map(const vector<vector<Tree>>& left, const vector<vector<Tree>>& right)
{
    vector<vector<Tree>> wrapped_map;
    
    for (int i = 0; i < left.size(); i++)
    {
        vector<Tree> line(left.size());
        for (int j = 0; j < left[i].size(); j++)
        {
            Tree tree;
            line[j].visible = left[i][j].visible || right[i][j].visible;
        }
        wrapped_map.push_back(line);
    }
    return wrapped_map;
}

vector<vector<Tree>> wrap_map(const vector<vector<Tree>>& left, const vector<vector<Tree>>& right,const vector<vector<Tree>>& up, const vector<vector<Tree>>& down)
{
    vector<vector<Tree>> wrapped_map;
    
    for (int i = 0; i < left.size(); i++)
    {
        vector<Tree> line(left.size());
        for (int j = 0; j < left[i].size(); j++)
        {
            Tree tree;
            line[j].visible = left[i][j].visible || right[i][j].visible || up[i][j].visible || down[i][j].visible;
        }
        wrapped_map.push_back(line);
    }
    return wrapped_map;
}

vector<vector<Tree>> make_map(vector<vector<int>>& square, const direction& viewer)
{
    vector<vector<Tree>> tree_map;
    if (viewer == UP || viewer == DOWN) square = rotate_left(square);
    for(auto line : square) tree_map.push_back(std::move(scan_line(line, viewer)));
    if (viewer == UP || viewer == DOWN) {
        square = rotate_right(square);
        tree_map = rotate_right(tree_map);
    }
    return tree_map;
}

vector<Tree> scan_line(vector<int> line, const direction& viewer)
{
    vector<Tree> scanned_line(line.size());
    if (viewer == RIGHT || viewer == DOWN) reverse(line.begin(), line.end());
    int tallest_sofar = -1;

    for (int i = 0; i < line.size(); i++)
    {
        int digit = line[i];
        if (digit > tallest_sofar)
        {
            tallest_sofar = digit;
            scanned_line[i].visible = VISIBLE;
        }
    }
    
    if(viewer == RIGHT || viewer == DOWN) reverse(scanned_line.begin(), scanned_line.end());
    return scanned_line;
}

vector<vector<int>> read_square(string file_name)
{
    vector<vector<int>> square;
    ifstream ifs;
    ifs.open(file_name);
    string a;
    while(getline(ifs,a))
    {
        square.push_back(read_line(a));
    }
    return square;
}

vector<int> read_line(string line)
{
    vector<int> digits;
    for(const char& ch : line)
    {
        digits.push_back(ch - ASCII_FOR_NUM);
    }
    return digits;
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

vector<vector<Tree>> rotate_right(const vector<vector<Tree>>& v)
{
    vector<vector<Tree>> rotated;
    for(int i = 0; i < v[0].size(); i++)
    {
        vector<Tree> line;
        for(int j  = v.size() - 1; j >= 0; j--)
        {
            line.push_back(v[j][i]);
        }
        rotated.push_back(line);
    }
    return rotated;
}

vector<vector<Tree>> rotate_left(const vector<vector<Tree>>& v)
{
    vector<vector<Tree>> rotated;
    for(int i = v[0].size() - 1; i >= 0; i--)
    {
        vector<Tree> line;
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