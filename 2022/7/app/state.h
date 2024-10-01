#pragma once
#include "dir.h"

class State{
public:
    Dir out_most = Dir("/");
    Dir* current_dir = &out_most;
};

int get_dir_size(const Dir& dir);

int find_lowest_to_delete(const int,const int);