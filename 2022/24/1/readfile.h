#pragma once
#include "std_lib_facilities.h"
#include "map.h"
#include "blizzard.h"

string FileName(int argc, char** argv);
Map ReadMap(const string& filename);
vector<Blizzard> ReadBlizzard(const string& filename, const Map& map);
