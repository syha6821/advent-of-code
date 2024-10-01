#include "std_lib_facilities.h"
#include "readfile.h"
#include "calc.h"

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    unordered_map<string,Monkey> monkeys = ReadFile(filename);
    
    // sample
    /* cout << monkeys.at("root").expression(monkeys) << '\n'; */

    // h
    /* string left =  monkeys.at("pppw").expression(monkeys); */
    /* long left =  monkeys.at("pppw").yell(monkeys); */
    /* long right =  monkeys.at("sjmn").yell(monkeys); */
    
    //input
    // h
    string left =  monkeys.at("mrnz").expression(monkeys);
    long right = monkeys.at("jwrp").yell(monkeys);

    cout << calc(left, right) << '\n';
    return 0;
}