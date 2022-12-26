/*
    g++ main.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
*/

#include <cassert>

#include "../../include/variant_cast.hpp"

using namespace variant_ext;

struct circle
{
    double _radius;
};

struct square
{
    double _side;
};

struct triangle
{
    double _angle1;
    double _angle2;
    double _angle3;
};

struct rectangle
{
    double _width;
    double _hight;
};

using shape = std::variant<circle,square,triangle,rectangle>; 

int main()
{
    using polygon4sides = std::variant<rectangle, square>;

    polygon4sides derived = square{3.1456};
    shape base = variant_cast<shape>(std::move(derived));
    assert(3.1456 == std::get<square>(base)._side);
}
