#pragma once
#include "std_lib_facilities.h"

class File{
public:
    File(string n, int s) : name(n), size(s){};
    string get_name() const;
    int get_size() const;

private:
    string name;
    string path;
    int size;
};