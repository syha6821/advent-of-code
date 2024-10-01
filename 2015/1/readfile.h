#pragma once
#include "std_lib_facilities.h"
#include "pattern.h"

string FileName(int argc, char** argv);
vector<Pattern> ReadPattern(string filename);
