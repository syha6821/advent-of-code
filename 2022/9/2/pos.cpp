#include "pos.h"

void Pos::R()
{
    this->shadow_x = x;
    this->shadow_y = y;
    this->x++;
}
void Pos::L()
{
    this->shadow_x = x;
    this->shadow_y = y;
    this->x--;
}
void Pos::U()
{
    this->shadow_x = x;
    this->shadow_y = y;
    this->y++;
}
void Pos::D()
{
    this->shadow_x = x;
    this->shadow_y = y;
    this->y--;
}
void Pos::do_command(char ch)
{
    switch (ch)
    {
    case 'L':
        this->L();
        break;
    case 'R':
        this->R();
        break;
    case 'U':
        this->U();
        break;
    case 'D':
        this->D();
        break;
    }
}
string Pos::hash()
{
    return 'x' + to_string(this->x) + 'y' + to_string(this->y);
}

bool Pos::is_adjacent(const Pos &H)
{
    int vertical = pow((H.get_x() - this->x),2);
    int horizontal = pow((H.get_y() - this->y),2);
    
    int distance = vertical + horizontal;
    return (distance == 2 || distance == 1 || distance == 0);
    /* return (distance == 2); */
}

void Pos::follow(const Pos& H)
{
    if(this->is_adjacent(H)) return;
    this->x = H.shadow_x;
    this->y = H.shadow_y;
}

ostream &operator<<(ostream &stream, const Pos &p)
{
    return stream << '(' << p.x << ',' << p.y << ')';
}