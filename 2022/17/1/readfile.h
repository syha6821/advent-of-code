#pragma once
#include "std_lib_facilities.h"
#include <bitset>
#include "chamber.h"
#include <fstream>
#include "rock.h"
#include "jet.h"

const string ROCK_FILENAME = "../rocks.txt";

string FileName(int argc, char** argv);

Rock::SLICE to_slice(string line);
Rock::SPRITE to_sprite(vector<string> lines);
vector<Rock> to_rocks(string rock_file_name);
vector<Jet> to_jet_pattern(string file_name);