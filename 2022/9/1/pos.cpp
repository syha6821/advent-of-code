#include "pos.h"

void Pos::R()
{
    this->x++;
}
void Pos::L()
{
    this->x--;
}
void Pos::U()
{
    this->y++;
}
void Pos::D()
{
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
    return (distance <= 2);
}

int Pos::distance_from(const Pos &H)
{
    int vertical = pow((H.get_x() - this->x), 2);
    int horizontal = pow((H.get_y() - this->y),2);

    return vertical + horizontal;
}

void Pos::follow(const Pos& H)
{
    int distance = this->distance_from(H);
    if(distance <= 2) return;
    int x = (H.get_x() > this->x)? 1 : -1;
    x = (H.get_x() == this->x)? 0 : x;
    int y = (H.get_y() > this->y)? 1 : -1;
    y = (H.get_y() == this->y)? 0 : y;

    this->x += x;
    this->y += y;
}

/* void Pos::follow(Pos& H) */
/* { */
/*     if(this->is_adjacent(H)) return; */
/* } */

ostream &operator<<(ostream &stream, const Pos &p)
{
    return stream << '(' << p.x << ',' << p.y << ')';
}