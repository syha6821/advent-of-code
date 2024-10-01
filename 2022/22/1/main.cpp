#include "std_lib_facilities.h"
#include "readfile.h"
#include "map.h"
#include "unit.h"

int main(int argc, char** argv)
{
    const string FILENAME = FileName(argc, argv);
    Map m = ReadMap(FILENAME);
    vector<pair<char, int>> patterns = ReadPattern(FILENAME);
    Unit unit(m);
    
    MovePattern(patterns, unit);

    return 0;
}