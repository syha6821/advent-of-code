#include "std_lib_facilities.h"
#include "readfile.h"
#include "cube.h"
#include "droplet.h"
#include <set>

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    unordered_set<Cube> cubes = read_cubes(filename);

    Droplet droplet(cubes);
    droplet.surface_size();
    cout << droplet.surface_size() << '\n';
    droplet.spreader();
    cout << droplet.stepped_size() << '\n';
    return 0;
}