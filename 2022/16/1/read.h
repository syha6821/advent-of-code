#pragma once
#include "std_lib_facilities.h"
#include "valve.h"
#include <fstream>


vector<Valve> read_file(string filename);

string get_name(const string& line);

int get_flow_rate(const string& line);

vector<string> get_near_valves_name(const string& line);