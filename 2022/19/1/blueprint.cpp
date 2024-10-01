#include "blueprint.h"

BluePrint::BluePrint(int id, vector<Recipe> recipes):id_(id)
{
    for (Recipe recipe : recipes)
    {
        if (recipe.ore() > ore_robot_limit) ore_robot_limit = recipe.ore();
        if (recipe.clay() > clay_robot_limit) clay_robot_limit = recipe.clay();
        if (recipe.obsidian() > obsidian_robot_limit) obsidian_robot_limit = recipe.obsidian();

        blueprint_.insert(make_pair(recipe.robot_type(), recipe));
    }
}

bool BluePrint::is_over_limit(const Resource& resource)
{
    if(resource.RobotCount(MaterialType::Ore) > ore_robot_limit) return true;
    if(resource.RobotCount(MaterialType::Clay) > clay_robot_limit) return true;
    if(resource.RobotCount(MaterialType::Obsidian) > obsidian_robot_limit) return true;

    return false;
}

int hightest(const unordered_set<Resource>& resources)
{
    int highest = 0;
    for(const Resource& resource : resources)
    {
        if(resource.geode() > highest) highest = resource.geode();
    }
    return highest;
}

const Recipe& BluePrint::recipe(MaterialType robot_type)
{
    return blueprint_.at(robot_type);
}

int BluePrint::calc(int time, unordered_set<Resource> resources)
{
    time++;
    unordered_set<Resource> next;
    for (const Resource &resource : resources)
    {
        for (const Resource &next_resource : NextResource(resource))
        {
            next.insert(next_resource);
        }
    }

    cout << "After Time " << time << " : resources size (" << next.size() << ")\n";

    if(time == GIVEN_TIME)
    {
        return hightest(next);
    }
    else
    {
        return calc(time, next);
    }
}

/* unordered_set<Resource> BluePrint::NextResource(const Resource& resource) */
/* { */
/*     unordered_set<Resource> next; */
/*     Resource origin = resource; */
/*     origin.OperateRobots(); */
/*     next.insert(origin); */

/*     Resource res = resource; */
/*     for(int i = 3; i >= 0; i--) */
/*     { */
/*         if (res.MakeRobot(recipe(MaterialType(i)))) */
/*         { */
/*             res.OperateRobots(); */
/*             res.ReleaseRobot(); */
/*             next.insert(res); */
/*             return next; */
/*         } */
/*     } */
/*     return next; */
/* } */

bool BluePrint::geode_satisfied(const Resource& resource)
{
    if(resource.ore() >= recipe(MaterialType::Geode).ore() && resource.obsidian() >= recipe(MaterialType::Geode).obsidian())
    {
        return true;
    }
    return false;
}

bool BluePrint::obsidian_satisfied(const Resource& resource)
{
    if(resource.ore() >= recipe(MaterialType::Obsidian).ore() && resource.clay() >= recipe(MaterialType::Obsidian).clay())
    {
        return true;
    }
    return false;
}

unordered_set<Resource> BluePrint::NextResource(const Resource& resource)
{
    unordered_set<Resource> next;
    set<MaterialType> new_wait_list;
    if(geode_satisfied(resource))
    {
        Resource res = resource;
        res.MakeRobot(recipe(MaterialType::Geode));
        res.OperateRobots();
        res.ResetWaitList();
        res.ReleaseRobot();
        if (not is_over_limit(res))
        {
            next.insert(std::move(res));
            return next;
        }
    }

    if(obsidian_satisfied(resource))
    {
        Resource res = resource;
        res.MakeRobot(recipe(MaterialType::Obsidian));
        res.OperateRobots();
        res.ResetWaitList();
        res.ReleaseRobot();
        if (not is_over_limit(res))
        {
            next.insert(std::move(res));
            return next;
        }
    }

    for(MaterialType robot : resource.wait_list())
    {
        Resource res = resource;
        if(res.MakeRobot(recipe(robot)))
        {
            res.OperateRobots();
            res.ReleaseRobot();
            res.ResetWaitList();
            if(not is_over_limit(res))
            {
                next.insert(std::move(res));
            }
        }        
        else
        {
            new_wait_list.insert(robot);
        }
    }

    if(not new_wait_list.empty())
    {
        Resource saver = resource;
        saver.OperateRobots();
        saver.ReplaceWaitList(std::move(new_wait_list));
        next.insert(std::move(saver));
    }

    return next;
}