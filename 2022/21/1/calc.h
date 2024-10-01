#include "std_lib_facilities.h"

long long operate(char op, long long x, long long y)
{
    switch (op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        error("Illegal operator\n");
        return (x == y);
    }
}

bool RemoveShell(string& str)
{
    if(str.front() == '(')
    {
        str = str.substr(1);
        str.pop_back();
        return true;
    }
    else
    {
        return false;
    }
}

pair<long long, char> GetNum(string& str)
{
    if(str[1] == '(')
    {
        stringstream ss( str.substr(str.find_last_of(')') + 1));
        long long num;
        ss >> num;
        return make_pair(num , 'b');
    }
    else if(isdigit(str[1]))
    {
        long long num = 0;
        stringstream ss(str.substr(1));
        ss >> num;
        return make_pair(num , 'f');
    }
    error("???\n");
    return make_pair(1,1);
}

char ReverseOp(char op)
{
    if (op == '+')
    {
        return '-';
    }
    if (op == '-')
    {
        return '+';
    }
    if (op == '*')
    {
        return '/';
    }
    if (op == '/')
    {
        return '*';
    }
    else
    {
        return false;
    }
}

long long calc(string left, long long right)
{
    cout << left << ':' << right << '\n';
    RemoveShell(left);
    if(left.find('(') == string::npos)
    {
        cout << "left : " << left << '\n';
        char op = left.front();
        long long num;
        int h_location = left.find('H');
        if(h_location == 1)
        {
            cout << "back\n";
            stringstream ss(left.substr(h_location + 1));
            ss >> num;
        }
        else
        {
            cout << "front\n";
            stringstream ss(left.substr(1));
            ss >> num;
            if(op == '/')
            {
                right = (num / right);
                return right;
            }
            if(op == '-')
            {
                right = num - right;
            }
        }
        return operate(ReverseOp(op),right, num);
    }
    else
    {
        char op = left.front();
        pair<long long, char> num = GetNum(left);
        
        if(op == '/' && num.second == 'f')
        {
            /* right = (1 / right) * num.first; */
            cout << "right\n";
            right = (num.first / right);
        }
        else if(op == '-' && num.second == 'f')
        {
            /* right = (1 / right) * num.first; */
            cout << "right\n";
            right = (num.first - right);
        }
        else
        {
            right = operate(ReverseOp(op), right, num.first);
        }
        left = left.substr(left.find_first_of('('), left.find_last_of(')'));
        
        return calc(left, right);
    }
}