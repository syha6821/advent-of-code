#include "std_lib_facilities.h"
#include <fstream>

const string SMALL = "small.txt";
const string SAMPLE = "sample.txt";
const string INPUT = "input.txt";

int sum_of_signal_strength(string recipe);

int main()
{
    int strength = sum_of_signal_strength(INPUT);
    cout << "strength : " << strength << '\n';
    return 0;
}


int sum_of_signal_strength(string recipe)
{
    ifstream ifs;
    ifs.open(recipe);
    string instruction;
    int register_ = 1;
    int cycle = 1;
    int strength = 0;
    bool is_doing_calc = false;
    while(ifs >> instruction)
    {
        cycle++;
        if(is_doing_calc)
        {
            register_ += stoi(instruction);
            is_doing_calc = false;
        }
        if(instruction == "noop")
        {
            continue;
        }
        if(instruction == "addx")
        {
            is_doing_calc = true;
        }
        if((cycle + 20) % 40 == 0)
        {
            strength += cycle * register_;
            cout << cycle << ':' << register_ << '\n';
        }
        cout << register_ << '\n';
    }
    return strength;
}