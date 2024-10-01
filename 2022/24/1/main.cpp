#include "std_lib_facilities.h"
#include "readfile.h"
#include "map.h"
#include "blizzard.h"
#include "unit.h"
#include <unordered_set>

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    Map map = ReadMap(filename);
    vector<Blizzard> blizzards = ReadBlizzard(filename,map);
    
    Unit first_unit(map);

    cout << FindPath(0, {first_unit}, blizzards, map) << '\n';
    
    first_unit.reverse_start_position();
    map.reverse_start_point();
    
    cout << FindPath(0, {first_unit}, blizzards, map) << '\n';

    first_unit.reverse_start_position();
    map.reverse_start_point();

    cout << FindPath(0, {first_unit}, blizzards, map) << '\n';

    return 0;
}
