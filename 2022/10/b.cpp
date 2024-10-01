#include "std_lib_facilities.h"
#include <fstream>

const string SMALL = "small.txt";
const string SAMPLE = "sample.txt";
const string INPUT = "input.txt";

string sprite(int position);
string draw(string recipe);

int main()
{
    string spp = "........................................";
    string result = draw(INPUT);
    for(int i = 0; i < result.size(); i++)
    {
        if (i % 40 == 0) cout << '\n';
        cout << result[i];
    }
    /* for(int i = 0; i < 21; i++) */
    /* { */
    /*     cout << result[i]; */
    /* } */
    cout << '\n';
    return 0;
}

string sprite(int position)
{
    cout << position <<'\n';
    /* string spp = "........................................"; */
    string spp = ".........................................";
    cout << "!\n";
    spp.replace(spp.begin()+position+1, spp.begin()+position+4, "###");
    spp.erase(spp.begin());
    cout << "?\n";
    return spp;
}

string draw(string recipe)
{
    ifstream ifs;
    ifs.open(recipe);
    string instruction;
    int register_ = 1;
    int cycle = 0;
    bool is_doing_calc = false;
    string result = "";
    string spr = sprite(0);

    while(ifs >> instruction)
    {
        cycle++;
        result += spr[cycle % 40];
        if(is_doing_calc)
        {
            register_ += stoi(instruction);
            is_doing_calc = false;
            cout << "regi : " << register_ << '\n';
            spr = sprite(register_);
        }
        if(instruction == "noop")
        {
            continue;
        }
        if(instruction == "addx")
        {
            is_doing_calc = true;
        }
    }
    cout << "cycle" << cycle << '\n';
    return result;
}