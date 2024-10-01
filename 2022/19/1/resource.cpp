#include "resource.h"
#include <bitset>

Resource::Resource()
{
    stones_.insert(make_pair(MaterialType::Ore, 0));
    stones_.insert(make_pair(MaterialType::Clay, 0));
    stones_.insert(make_pair(MaterialType::Obsidian, 0));
    stones_.insert(make_pair(MaterialType::Geode, 0));

    robots_.insert(make_pair(MaterialType::Ore, 1));
    robots_.insert(make_pair(MaterialType::Clay, 0));
    robots_.insert(make_pair(MaterialType::Obsidian, 0));
    robots_.insert(make_pair(MaterialType::Geode, 0));

    robots_in_factory_.insert(make_pair(MaterialType::Ore, 0));
    robots_in_factory_.insert(make_pair(MaterialType::Clay, 0));
    robots_in_factory_.insert(make_pair(MaterialType::Obsidian, 0));
    robots_in_factory_.insert(make_pair(MaterialType::Geode, 0));
    
    ResetWaitList();
}

bool Resource::is_enough(const Recipe &recipe)
{
    bool ore_enough = recipe.ore() <= stones_[MaterialType::Ore];
    bool clay_enough = recipe.clay() <= stones_[MaterialType::Clay];
    bool obsidian_enough = recipe.obsidian() <= stones_[MaterialType::Obsidian];

    return ore_enough && clay_enough && obsidian_enough;
}

bool Resource::MakeRobot(const Recipe &recipe)
{
    if(not is_enough(recipe))
    {
        return false;
    }

    stones_[MaterialType::Ore] -= recipe.ore();
    stones_[MaterialType::Clay] -= recipe.clay();
    stones_[MaterialType::Obsidian] -= recipe.obsidian();

    robots_in_factory_[recipe.robot_type()]++;
    return true;
}

void Resource::ReleaseRobot()
{
    for (int i = 0; i < 4; i++)
    {
        robots_[MaterialType(i)] += robots_in_factory_[MaterialType(i)];
        robots_in_factory_[MaterialType(i)] = 0;
    }
}

void Resource::OperateRobots()
{
    for(const auto& robot : robots_)
    {
        stones_[robot.first] += robot.second;
    }
}