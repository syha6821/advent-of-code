#include "std_lib_facilities.h"
#include <stack>

vector<char> read_stack_line(string line)
{
    vector<char> stack_line;
    for (int i = 1; i < 35; i += 4)
    {
        stack_line.push_back(line[i]);
    }
    return stack_line;
}

vector<vector<char>> read_stack(ifstream& input)
{
    string line;
    vector<char> tokens;
    vector<vector<char>> vectors(9);
    while(getline(input,line))
    {
        if(line.find('[') == -1) break;
        tokens = read_stack_line(line);
        for(int i = 0; i < tokens.size(); i++)
        {
            if(!tokens.empty())
            {
                vectors[i].push_back(tokens[i]);
            }
        }
    }
    return vectors;
}

vector<stack<char>> make_stack(vector<vector<char>> vectors)
{
    vector<stack<char>> stacks(9);
    for (int i = 0; i < vectors.size(); i++)
    {
        reverse(vectors[i].begin(), vectors[i].end());
        for(char ch : vectors[i])
        {
            if(!isblank(ch)) stacks[i].push(ch);
        }
    }
    return stacks;
}

vector<int> get_command_nums(string str)
{
    vector<int> nums;
    string temp;
    for(int i = 0; i < str.size(); i++)
    {
        char ch = str[i];
        if(ch != ' ') temp += ch;
        if(ch == ' ')
        {
            if (isdigit(temp[0])) nums.push_back(stoi(temp));
            temp = "";
        }
        if(i == str.size()-1)
        {
            nums.push_back(stoi(temp));
        }
    }
    return nums;
}

void do_command(string cmd, vector<stack<char>>& stacks)
{
    vector<int> nums = get_command_nums(cmd);
    int move = nums[0];
    int from = nums[1] - 1;
    int to = nums[2] - 1;
    stack<char> tmp_stack;
    for(int i = 0; i < move; i++)
    {
        tmp_stack.push(stacks[from].top());
        stacks[from].pop();
    }
    while(!tmp_stack.empty())
    {
        stacks[to].push(tmp_stack.top());
        tmp_stack.pop();
    }
}

int main()
{
    ifstream input;
    input.open("input.txt");
    auto stacks = make_stack(read_stack(input));
    string cmd;
    while(getline(input,cmd))
    {
        if (cmd != "") do_command(cmd,stacks);
    }
    for(auto stack : stacks)
    {
        while(!stack.empty())
        {
            cout << '[' << stack.top() << ']' << ' ';
            stack.pop();
        }
        cout << '\n';
    }

    return 0;
}