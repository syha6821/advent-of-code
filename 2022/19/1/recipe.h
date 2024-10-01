#pragma once
#include "material.h"
#include <set>

class Recipe
{
public:
    Recipe(MaterialType robot_type, int ore, int clay, int obsidian) : robot_type_(robot_type), ore_(ore), clay_(clay), obsidian_(obsidian){};
    MaterialType robot_type() const { return robot_type_; };
    int ore() const { return ore_; };
    int clay() const { return clay_; };
    int obsidian() const { return obsidian_; };

private:
    MaterialType robot_type_;
    const int ore_ = 0;
    const int clay_ = 0;
    const int obsidian_ = 0;
};