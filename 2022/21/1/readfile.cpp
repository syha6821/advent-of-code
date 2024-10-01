#include "readfile.h"
#include <fstream>
#include "expr.h"

string FileName(int argc, char** argv)
{
    const string INPUT = "../input.txt";
    const string SAMPLE = "../sample.txt";
    const string SAMPLE2 = "../sample2.txt";
    string file_name;
    
    if (argc == 1)
    {
        return SAMPLE;
    }
    else if (string(argv[1]) == "input")
    {
        return INPUT;
    }
    else if (string(argv[1]) == "sample2")
    {
        return SAMPLE2;
    }
    else
    {
        return SAMPLE;
    }
}

Monkey ReadMonkey(const string& line)
{
    stringstream ss(line);
    vector<string> expr;

    string name;
    getline(ss, name, ':');

    string left;
    getline(ss, left, ' ');
    getline(ss, left, ' ');
    expr.push_back(left);
    
    if(isdigit(left[0]))
    {
        return Monkey(name,Expr(expr));
    }

    string op;
    getline(ss, op, ' ');
    if(name == "root")
    {
        expr.push_back("=");
    }
    else
    {
        expr.push_back(op);
    }

    string right;
    getline(ss, right, ' ');
    expr.push_back(right);
    
    return Monkey(name, Expr(expr));
}

unordered_map<string, Monkey> ReadFile(string filename)
{
    unordered_map<string, Monkey> monkeys;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        Monkey monkey = ReadMonkey(line);
        monkeys.insert(make_pair(monkey.name(), monkey));
    }
    return monkeys;
}
