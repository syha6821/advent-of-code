#pragma once
#include "std_lib_facilities.h"
#include <fstream>
#include "blueprint.h"
#include "recipe.h"

string FileName(int argc, char** argv);

vector<int> extract_nums(string str);
vector<BluePrint> ReadBluePrint(string filename);