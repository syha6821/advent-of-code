#pragma once

enum class Material
{
    Empty = '@', Rock = '#' , Air = '.'
};

inline ostream& operator<< (ostream& os, const Material& material)
{
    os << (char)material;
    return os;
}

inline Material get_value_of(char ch)
{
    switch (ch)
    {
    case '@':
        return Material::Empty;

    case '#':
        return Material::Rock;

    case '.':
        return Material::Air;
    
    default:
        return Material::Empty;
    }
}