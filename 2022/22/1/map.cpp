#include "map.h"

vector<vector<char>> rotated(const vector<vector<char>>& square)
{
    int origin_height = square.size();
    int width = square[0].size();

    vector<vector<char>> rotated_square(width);
    for (int i = origin_height - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            rotated_square[j].push_back(square[i][j]);
        }
    }
    return rotated_square;
}

Position Map::start_position() const
{
    return Position(find_first_not_empty(map_, 1));
}

Position Map::find_first_not_empty(const vector<vector<char>> &map, int row_num) const
{
    const vector<char>& row = map.at(row_num);
    for(int i = 0; i < row.size(); i++)
    {
        if(row[i] != (char)Material::Empty)
        {
            return Position(row_num, i);
        }
    }
    error("Can not find empty\n");
    return Position(-1,-1);
}

Position Map::find_last_not_empty(const vector<vector<char>> &map, int row_num) const
{
    const vector<char>& row = map.at(row_num);
    for(int i = row.size() - 1; i >= 0; i--)
    {
        if(row[i] != (char)Material::Empty)
        {
            return Position(row_num, i);
        }
    }
    error("Can not find empty\n");
    return Position(-1,-1);
}

Position Map::LinkedPosition(const Position &pos, Direction direction) const
{
    if(direction == Direction::Left)
    {
        return find_last_not_empty(map_,pos.row());
    }
    if(direction == Direction::Right)
    {
        return find_first_not_empty(map_,pos.row());
    }
    if(direction == Direction::Down)
    {
        return LeftRotatedPosition(find_last_not_empty(rotated_map_, RightRotatedPosition(pos).row()));
    }
    if(direction == Direction::Up)
    {
        return LeftRotatedPosition(find_first_not_empty(rotated_map_, RightRotatedPosition(pos).row()));
    }
    error("Can not find Such Linked Position\n");
    return Position(-1,-1);
}


ostream &operator<<(ostream &stream, const Map &map)
{
    for(auto row : map.map_)
    {
        for(auto item : row)
        {
            stream << item;
        }
        stream << '\n';
    }
    return stream;
}