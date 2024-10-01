#pragma once
#include "std_lib_facilities.h"
#include "map.h"
#include "material.h"
#include "area.h"

string FileName(int argc, char** argv);
Map ReadMap(const string& filename);
vector<pair<char,int>> ReadPattern(const string& filename);