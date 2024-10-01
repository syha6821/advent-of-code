#include "logic.h"
#include "dir.h"
#include "file.h"
#include "state.h"

bool is_digit(const string& str)
{
    for(const char& ch : str)
    {
        if(!isdigit(ch)) return false;
    }
    return true;
}

void read_line(const string& line, State& state)
{
    stringstream st(line);
    string indicator;
    st >> indicator;
    if(indicator == "$")
    {
        read_command(st,state);
    }
    else if(is_digit(indicator))
    {
        putback_string(st,indicator);
        read_file(st,state);
    }
    else if(indicator == "dir")
    {
        read_dir(st,state);
    }
    else
    {
        error("Invalid line : " + line);
    }
}

State read_lines(string input_file_name)
{
    ifstream isf;
    State state;
    isf.open(input_file_name);
    string line;
    while(getline(isf,line))
    {
        read_line(line,state);
    }
    return state;
}

void read_command(stringstream& st,State& state)
{
    string command;
    st >> command;
    if (command == "cd")
    {
        string dir_name;
        st >> dir_name;
        if (dir_name == "..")
        {
            cout << "before .. current : " << state.current_dir->get_name() << '(' << state.current_dir << ")\n";
            state.current_dir = state.current_dir->get_parent();
            cout << "after .. current : " << state.current_dir->get_name() << '(' << state.current_dir << ")\n";
        }
        else
        {
            if(dir_name == "/")
            {
                return;
            }
            state.current_dir = state.current_dir->get_sub_dir(dir_name);
        }
    }
    else if (command == "ls")
    ; // do nothing
}

void read_file(stringstream& st,State& state)
{
    string size_str;
    st >> size_str;
    int file_size = stoi(size_str);
    string file_name;
    st >> file_name;
    state.current_dir->add_file(std::move(File(file_name,file_size)));
    cout << "add file "<< file_name << " to : " << state.current_dir->get_name() << '(' << state.current_dir << ')' <<'\n';
}

void read_dir(stringstream& st,State& state)
{
    string dir_name;
    st >> dir_name;
    cout << "read dir : " << dir_name << " at : " << state.current_dir->get_name() << '(' << state.current_dir << ')' << '\n';
    state.current_dir->add_dir(std::move(Dir(dir_name,state.current_dir)));
    /* state.current_dir->add_dir(std::move(Dir(dir_name))); */
}

void putback_string(stringstream& st,string str)
{
    reverse(str.begin(), str.end());
    for(const char& ch : str)
    {
        st.putback(ch);
    }
}