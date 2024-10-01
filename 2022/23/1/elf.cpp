#include "elf.h"

bool Elf::is_empty_direction(const unordered_set<Position> &elves_positions, const Direction& direction) const
{
    for(const Position& position : pos_.positions_at(direction))
    {
        if (elves_positions.count(position)) return false;
    }
    return true;
}

Direction Elf::next_empty_direction(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const
{
    for(const Direction& direction : look_order)
    {
        if (is_empty_direction(elves_positions, direction)) return direction;
    }
    return Direction::Current;
}

vector<Direction> Elf::empty_directions(const unordered_set<Position>& elves_positions, const vector<Direction>& look_order) const
{
    vector<Direction> empties;
    for(const Direction& direction : look_order)
    {
        if (is_empty_direction(elves_positions, direction)) empties.push_back(direction);
    }
    return empties;
}

bool Elf::can_move(const unordered_set<Position> &elves_positions, const vector<Direction> &look_order) const
{
    if(next_empty_direction(elves_positions, look_order) == Direction::Current)
    {
        return false;
    }
    return true;
}

bool Elf::not_move(const unordered_set<Position> &elves_positions, const vector<Direction> &look_order) const
{
    if(empty_directions(elves_positions, look_order).size() == 4)
    {
        return true;
    }
    return false;
}

Position Elf::propose(const unordered_set<Position> &elves_positions, const vector<Direction> &look_order) const
{
    return pos_.at(next_empty_direction(elves_positions, look_order));
}

unordered_set<Position> elves_positions(const unordered_set<Elf>& elves)
{
    unordered_set<Position> positions;
    for(const Elf& elf : elves)
    {
        positions.insert(elf.pos());
    }
    return positions;
}

unordered_map<Position, vector<Elf>> proposed_positions(const unordered_set<Elf>& elves, const vector<Direction>& look_order)
{
    unordered_map<Position, vector<Elf>> proposed;
    unordered_set<Position> current_positions = elves_positions(elves);
    for(const Elf& elf : elves)
    {
        if(elf.can_move(current_positions, look_order) && not elf.not_move(current_positions, look_order))
        {
            Position proposing_pos = elf.propose(current_positions, look_order);
            if(proposed.count(proposing_pos))
            {
                proposed[proposing_pos].push_back(elf);
            }
            else
            {
                proposed.insert({proposing_pos, {elf}});
            }
        }
    }
    return proposed;
}

unordered_set<Elf> not_or_cant_move_elves(const unordered_set<Elf>& elves, const vector<Direction>& look_order)
{
    unordered_set<Elf> not_moving;
    unordered_set<Position> current_positions = elves_positions(elves);
    for(const Elf& elf : elves)
    {
        if(not elf.can_move(current_positions, look_order))
        {
            not_moving.insert(elf);
        }
        if(elf.not_move(current_positions, look_order))
        {
            not_moving.insert(elf);
        }
    }
    return not_moving;
}

unordered_set<Elf> not_moving_elves(const unordered_set<Elf>& elves, const vector<Direction>& look_order)
{
    unordered_set<Elf> not_moving;
    unordered_set<Position> current_positions = elves_positions(elves);
    for(const Elf& elf : elves)
    {
        if(elf.not_move(current_positions, look_order))
        {
            not_moving.insert(elf);
        }
    }
    return not_moving;
}

int calc_map_size(const unordered_set<Elf>& elves)
{
    Elf first_elf = *elves.begin();
    int top_most = first_elf.pos().row();
    int bottom_most = first_elf.pos().row();
    int right_most = first_elf.pos().column();
    int left_most = first_elf.pos().column();
    
    for(const Elf& elf : elves)
    {
        int row = elf.pos().row();
        int column = elf.pos().column();
        
        if(row < top_most) top_most = row;
        if(row > bottom_most) bottom_most = row;

        if(column < left_most) left_most = column;
        if(column > right_most) right_most = column;
    }

    return (right_most - left_most + 1) * (bottom_most - top_most + 1);
}

int expand(const unordered_set<Elf>& elves, const vector<Direction>& look_order, int round)
{
    round++;
    cout << round << '\n';
    unordered_map<Position, vector<Elf>> proposed = proposed_positions(elves, look_order);
    unordered_set<Elf> next_elves = not_or_cant_move_elves(elves, look_order);
    /* if(round == 5 || not_moving_elves(elves, look_order).size() == elves.size()) */
    /* if(round == 11 || not_moving_elves(elves, look_order).size() == elves.size()) */
    if(not_moving_elves(elves, look_order).size() == elves.size())
    {
        for(const Elf& elf : elves)
        {
            cout << elf.pos().row() << ',' << elf.pos().column() << '\n';
        }
        /* return (calc_map_size(elves) - elves.size()); */
        return round;
    }
    for(auto position : proposed)
    {
        if(position.second.size() == 1)
        {
            Elf elf = position.second.front();
            elf.move(position.first);
            next_elves.insert(elf);
        }
        else
        {
            for(const Elf& elf : position.second)
            {
                next_elves.insert(elf);
            }
        }
    }
    return expand(next_elves, next_direction(look_order), round);
}