#pragma once
#include "std_lib_facilities.h"
#include "file.h"

class Dir{
public:
    Dir(){};
    Dir(string n):name(n){};
    Dir(string n, Dir* p):name(n),parent(p){};
    Dir* get_parent();
    Dir* get_sub_dir(const string& name);
    string get_name() const;
    void add_file(const File& file);
    void add_dir(const Dir& dir);
    const vector<Dir>& get_sub_dirs() const;
    const vector<File>& get_sub_files() const;

private:
    string name;
    string path;
    int size;
    Dir* parent;
    vector<Dir> sub_dirs;
    vector<File> sub_files;
};