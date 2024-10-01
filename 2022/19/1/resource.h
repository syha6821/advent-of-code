#pragma once
#include "material.h"
#include "std_lib_facilities.h"
#include "recipe.h"
#include <set>
#include <map>

class Resource
{
public:
    Resource();
    void OperateRobots();
    void Add(MaterialType material) { stones_[material]++; };
    bool MakeRobot(const Recipe& recipe);
    void ReleaseRobot();
    int geode() const { return stones_.at(MaterialType::Geode); };

    int ore() const { return stones_.at(MaterialType::Ore); };
    int clay() const { return stones_.at(MaterialType::Clay); };
    int obsidian() const { return stones_.at(MaterialType::Obsidian); };
    
    const map<MaterialType, int>& stones() const { return stones_; };

    int hash_num() const
    {
        int s = stones_.size();
        int r = robots_.size();
        int h = (s + r) * (s + r + 1) / 2 + s;
        return h;
    }

    bool operator==(const Resource& resource) const
    {
        return (stones_ == resource.stones_ && robots_ == resource.robots_);
    }
    
    const set<MaterialType>& wait_list() const { return wait_list_; };
    
    void ResetWaitList()
    {
        set<MaterialType> new_wait_list;
        
        for(int i = 0; i < robots_.size() + 1; i++)
        {
            if(i == 4) break;
            new_wait_list.insert(MaterialType(i));
        }

        wait_list_ = new_wait_list;
    }

    void ReplaceWaitList(const set<MaterialType>& new_wait_list) { wait_list_ = new_wait_list; };
    int RobotCount(MaterialType robot_type) const { return robots_.at(robot_type); };
    

private:
    bool is_enough(const Recipe& recipe);
    map<MaterialType,int> stones_;
    map<MaterialType,int> robots_;
    map<MaterialType,int> robots_in_factory_;
    
    set<MaterialType> wait_list_;
};

namespace std
{
    template<>
    struct hash<Resource>
    {
        size_t operator()(const Resource& resource) const
        {
            return resource.hash_num();
        }
    };
}