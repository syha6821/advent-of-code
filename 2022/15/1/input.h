#pragma once
#include "std_lib_facilities.h"
#include "sensor.h"
#include <fstream>

vector<Sensor> read_file(string filename);

pair<int, int> read_xy(string line);