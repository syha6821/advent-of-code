#include "std_lib_facilities.h"
#include "readfile.h"
#include "direction.h"

int main(int argc, char** argv)
{
    const string FILENAME = FileName(argc, argv);
    unordered_set<Elf> elves = ReadElves(FILENAME);
    vector<Direction> default_directions = default_direction();
    
    cout << expand(elves, default_directions, 0) << '\n';
    

    return 0;
}