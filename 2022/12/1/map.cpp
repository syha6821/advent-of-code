#include "map.h"

bool Map::is_valid_point(Point point)
{
    bool is_valid = point.x >= 0 && point.y >= 0 && (point.x < width) && (point.y < height);
    return is_valid;
}