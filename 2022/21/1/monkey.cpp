#include "monkey.h"

long calculate(char op, long x, long y)
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
        return (x == y);
    }
}

long long Monkey::yell(const unordered_map<string, Monkey>& monkeys) const
{
    if (expr_.is_num())
    {
        return expr_.num();
    }
    else
    {
        const Monkey& l_monkey = monkeys.at(expr_.left());
        const Monkey& r_monkey = monkeys.at(expr_.right());
        return calculate(expr_.op(), l_monkey.yell(monkeys), r_monkey.yell(monkeys));
    }
}

string Monkey::expression(const unordered_map<string, Monkey>& monkeys) const
{
    if(name_ == "humn")
    {
        return "H";
    }
    else if(expr_.is_num())
    {
        return to_string(expr_.num());
    }
    else
    {
        const Monkey& l_monkey = monkeys.at(expr_.left());
        const Monkey& r_monkey = monkeys.at(expr_.right());

        string l_expr = l_monkey.expression(monkeys);
        string r_expr = r_monkey.expression(monkeys);

        if (l_expr.find('H') == string::npos)
        {
            l_expr = to_string(l_monkey.yell(monkeys));
        }

        if (r_expr.find('H') == string::npos)
        {
            r_expr = to_string(r_monkey.yell(monkeys));
        }

        return "(" + to_string(expr_.op()) + l_expr + " " + r_expr + ")";
    }
}