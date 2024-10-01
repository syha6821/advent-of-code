#include "std_lib_facilities.h"
#include "readfile.h"
#include "blueprint.h"

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    vector<BluePrint> blueprints = ReadBluePrint(filename);
    cout << filename << '\n';
    
    int result = blueprints[0].calc();

    cout << "result : " << result << '\n';

    /* int result = 1; */
    /* for(BluePrint blueprint : blueprints) */
    /* { */
    /*     result *= blueprint.calc(); */
    /* } */

    /* cout << "result : " << result << '\n'; */
    return 0;
}