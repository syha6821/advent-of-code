#pragma once
#include "std_lib_facilities.h"
#include "cube.h"

string FileName(int argc, char** argv);
unordered_set<Cube> read_cubes(string filename);