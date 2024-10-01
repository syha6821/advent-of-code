#pragma once
#include "std_lib_facilities.h"
#include <unordered_set>
#include "elf.h"

string FileName(int argc, char** argv);
unordered_set<Elf> ReadElves(const string& filename);