#pragma once
#include "std_lib_facilities.h"
#include "material.h"
#include "direction.h"
#include "position.h"
#include <map>

class Area
{
public:
    Area(Material material, Position pos):material_(material), position_(pos){};
    Position pos() const { return position_; };
    int row() const { return position_.row(); };
    int column() const { return position_.column(); };
    void changeMaterial(Material material) { material_ = material; };
    Material material() const { return material_; };

    string lineAt(Direction direction) { return line_names_[direction]; };
    void AddOwnerLineName(Direction direction ,string line_name) { line_names_.insert(make_pair(direction, line_name)); };
    friend ostream &operator<<(ostream &os, const Area &area);

private:
    Position position_;
    Material material_;
    map<Direction, string> line_names_;
};

inline ostream& operator<< (ostream& os, const Area& area)
{
    os << area.material_;
    return os;
}