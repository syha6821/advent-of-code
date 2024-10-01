#pragma once
#include "std_lib_facilities.h"
#include <map>
#include <unordered_set>
#include "material.h"
#include "recipe.h"
#include "resource.h"

class BluePrint
{
public:
    const int GIVEN_TIME = 32;
    BluePrint(int id, vector<Recipe> recipes);
    int const id() { return id_; };
    const Recipe& recipe(MaterialType robot_type);
    int calc(int time = 0, unordered_set<Resource> resources = {Resource()});
    unordered_set<Resource> NextResource(const Resource &);
    bool is_over_limit(const Resource&);
    bool geode_satisfied(const Resource &resource);
    bool obsidian_satisfied(const Resource &resource);

private:
    int ore_robot_limit = 0;
    int clay_robot_limit = 0;
    int obsidian_robot_limit = 0;
    int id_;
    map<MaterialType, Recipe> blueprint_;
};