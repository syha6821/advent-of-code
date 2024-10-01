#include "packet.h"

List read_list(string line);
string trim_bracket(string str);

Packet::Packet(string line, int divider_flag):list(read_list(trim_bracket(line))),divider(divider_flag){};

Packet::Packet(string line):list(read_list(trim_bracket(line))){};

string trim_bracket(string str)
{
    if(str[0] != '[' && str.back() != ']') error("Square brackets are missing in line : " + str);
    str.erase(0,1);
    str.erase(str.size() - 1);
    return str;
}

List read_list(string line)
{
    vector<Value> values;
    stringstream ss(line);
    while(ss)
    {
        char ch =ss.get();
        if(ch == ',') continue;
        if(isdigit(ch))
        {
            ss.putback(ch);
            int num;
            ss >> num;
            values.push_back(Value(num));
        }
        if(ch == '[')
        {
            string list;
            getline(ss, list, ']');
            values.push_back(Value(read_list(list)));
        }
    }

    return List(values);
}