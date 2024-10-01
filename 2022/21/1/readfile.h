#pragma once
#include "std_lib_facilities.h"
#include <unordered_map>
#include "monkey.h"

string FileName(int argc, char** argv);
unordered_map<string, Monkey> ReadFile(string filename);