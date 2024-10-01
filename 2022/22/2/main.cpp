#include "std_lib_facilities.h"
#include "readfile.h"
#include "map.h"
#include "unit.h"
#include "side.h"

/* const int Side::WIDTH = 4; */
const int Side::WIDTH = 50;

int main(int argc, char** argv)
{
    const string FILENAME = FileName(argc, argv);
    Map m = ReadMap(FILENAME);
    vector<pair<char, int>> patterns = ReadPattern(FILENAME);
    Unit unit(m);
    
    cout << m << '\n';
    MovePattern(patterns, unit);
    
    /* int count = 1; */
    /* for(Line line  : m.lines()) */
    /* { */
    /*     cout << line << ' ' << line.at(0) << "->" << line.at_last() << '\n'; */
    /*     if (count % 4 == 0) cout << '\n'; */
    /*     count++; */
    /* } */
    return 0;
}