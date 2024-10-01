#include "std_lib_facilities.h"
#include "readfile.h"
#include "chamber.h"
#include "jet.h"
#include "logic.h"

int main(int argc, char** argv)
{
    /* const int Round = 2022; */
    const long Round = 1000000000000;
    const string FILENAME = FileName(argc, argv);
    vector<Rock> rocks = to_rocks(ROCK_FILENAME);
    vector<Jet> jet_pattern = to_jet_pattern(FILENAME);

    /* for (Rock rock : rocks) */
    /* { */
    /*     cout << rock << '\n'; */
    /* } */

    Chamber chamber;
    drop_rock(rocks, jet_pattern, chamber, Round);

    return 0;
}