#pragma once
#include "std_lib_facilities.h"
#include <fstream>
#include "map.h"

Map read_input(string filename);
Map read_reverse_map(string filename);