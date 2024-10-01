#include "map.h"

Map::Map(const vector<vector<Area>> &m) : map_(m)
{
    ReadLines_(start_position(), default_points_, Direction::Current);
    /* ReadLines(start_position(), Side(default_points_)); */
}

bool Map::is_valid_position(const Position &pos)
{
    bool valid_row = (0 <= pos.row()) &&  (pos.row() < height());
    bool valid_column = (0 <= pos.column()) &&  (pos.column() < width());
    return (valid_row && valid_column);
}

void Map::ReadLines_(Position top_left_position, const Side &side, Direction before_direction)
{
    ReadLines(top_left_position, side, before_direction);
    cout << "lines size : " << lines_.size() << '\n';
    if(lines_.size() == 24)
    {
        return;
    }
    else
    {
        Position up = Position(top_left_position.row() - Side::WIDTH, top_left_position.column());
        Position right = Position(top_left_position.row(), top_left_position.column() + Side::WIDTH);
        Position left = Position(top_left_position.row(), top_left_position.column() - Side::WIDTH);
        Position down = Position(top_left_position.row() + Side::WIDTH, top_left_position.column());

        if(before_direction != Direction::Down && is_valid_position(up) && at(up).material() != Material::Empty)
        {
            ReadLines_(up, side.adjacent_up_side(), Direction::Up);
        }
        if(before_direction != Direction::Left && is_valid_position(right) && at(right).material() != Material::Empty)
        {
            ReadLines_(right, side.adjacent_right_side(), Direction::Right);
        }
        if(before_direction != Direction::Up && is_valid_position(down) && at(down).material() != Material::Empty)
        {
            ReadLines_(down, side.adjacent_down_side(), Direction::Down);
        }
        if(before_direction != Direction::Right && is_valid_position(left) && at(left).material() != Material::Empty)
        {
            ReadLines_(left, side.adjacent_left_side(), Direction::Left);
        }
    }
}

void Map::ReadLines(Position top_left_position, const Side &side, Direction direction)
{
    Line up = side.up();
    Line right = side.right();
    Line down = side.down();
    Line left = side.left();

    for(int i = top_left_position.column() ; i < top_left_position.column() + Side::WIDTH; i++)
    {
        up.AddArea(at(Position(top_left_position.row(), i)));
    }

    for(int i = top_left_position.row() ; i < top_left_position.row() + Side::WIDTH; i++)
    {
        right.AddArea(at(Position(i, top_left_position.column() + Side::WIDTH - 1)));
    }

    for(int i = top_left_position.column() + Side::WIDTH - 1; i >= top_left_position.column(); i--)
    {
        down.AddArea(at(Position(top_left_position.row() + Side::WIDTH - 1, i)));
    }

    for (int i = top_left_position.row() + Side::WIDTH - 1; i >= top_left_position.row(); i--)
    {
        left.AddArea(at(Position(i, top_left_position.column())));
    }

    lines_.push_back(up);
    lines_.push_back(right);
    lines_.push_back(down);
    lines_.push_back(left);
}

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
    cout << "start position start\n";
    Position position = Position(find_first_not_empty(1));
    cout << "start position end\n";
    return Position(find_first_not_empty(1));
}

Position Map::find_first_not_empty(int row_num) const
{
    const vector<Area>& row = map_.at(row_num);
    for(int i = 0; i < row.size(); i++)
    {
        if(row[i].material() != Material::Empty)
        {
            return Position(row_num, i);
        }
    }
    error("Can not find empty\n");
    return Position(-1,-1);
}

Position Map::LinkedPosition(const Position &pos, Direction& direction)
{
    Area& area = at(pos);
    string line_name = area.lineAt(direction);
    int current_pos = 0;

    for(Line& line : lines_)
    {
        if(line.name() == line_name && direction == line.direction())
        {
            for(int i = 0; i < Side::WIDTH; i++)
            {
                if(line.at(i) == pos)
                {
                    current_pos = i;
                }
            }
        }
    }
    

    for(Line& line : lines_)
    {
        if(line.name() == line_name && direction != line.direction())
        {
            direction = reversed_direction(line.direction());
            return line.at(current_pos);
        }
        else if(line.reverse_name() == line_name)
        {
            cout << "changed direction : " << direction_string(direction) << " to ";
            direction = reversed_direction(line.direction());
            cout << direction_string(direction) << '\n';
            return line.at(Side::WIDTH - 1 - current_pos);
        }
    }
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