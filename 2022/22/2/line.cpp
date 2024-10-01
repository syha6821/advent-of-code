#include "line.h"

Line::Line(pair<Point, Point> points, Direction direction):
name_(points.first.to_string() + points.second.to_string()), reverse_name_(points.second.to_string() + points.first.to_string()),direction_(direction) { }

void Line::AddArea(Area& area) 
{
    area.AddOwnerLineName(direction_, name_);
    areas_.push_back(&area);
}
