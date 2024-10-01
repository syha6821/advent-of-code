#pragma once
#include "std_lib_facilities.h"
#include "state.h"
#include <fstream>

void read_line(const string& line,State& state);
/* void read_lines(string input_file_name); */
State read_lines(string input_file_name);
bool is_digit(const string& str);
void read_command(stringstream& st,State& state);
void read_file(stringstream& st,State& state);
void read_dir(stringstream& st, State& state);
void putback_string(stringstream& st,string str);