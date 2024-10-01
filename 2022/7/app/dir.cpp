#include "dir.h"

Dir* Dir::get_parent(){
    return parent;
}

const vector<Dir>& Dir::get_sub_dirs() const
{
    return sub_dirs;
}

string Dir::get_name() const
{
    return name;
}

Dir* Dir::get_sub_dir(const string& name)
{
    for(Dir& dir : sub_dirs)
    {
        if (dir.get_name() == name) { return &dir; };
    }
    error("There is no directory named " + name);
}

void Dir::add_file(const File& file)
{
    for(File f : sub_files)
    {
        if(f.get_name() == file.get_name()) return;
    }
    sub_files.push_back(std::move(file));
}

void Dir::add_dir(const Dir &dir)
{
    for(const Dir& d : sub_dirs)
    {
        if(d.get_name() == dir.get_name()) return;
    }
    sub_dirs.push_back(std::move(dir));
    cout << "pushed : " << dir.get_name() << " to : "<< this->get_name()<< '(' << this << ')' << '\n';
}

const vector<File>& Dir::get_sub_files() const
{
    return sub_files;
}