/*
    g++ main.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
*/

#include <cassert>
#include <vector>
#include <array>

#include "../../include/variant_visit.hpp"

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
using input = std::vector<double>; 
using output = std::array<double,2>; 

shape accept(circle const&, input const&, output&) {
    // ..
    return square{};
}

auto accept(square const&, input const&, output&) {
    // ..
    return std::variant<triangle>{};
}

auto accept(triangle const&, input const&, output&) {
    // ..
    return std::variant<rectangle>{rectangle{1 ,2}}; 
}

shape accept(rectangle const&, input const&, output&) {
    // ..
    return circle{3.1456};
}

int main()
{
    input in;
    output out;
    shape s;

    assert(std::holds_alternative<circle>(s));

    s = variant_ext::visit(s, in, out);
    assert(std::holds_alternative<square>(s));

    s = variant_ext::visit(s, in, out);
    assert(std::holds_alternative<triangle>(s));

    s = variant_ext::visit(s, in, out);
    assert(std::holds_alternative<rectangle>(s));

    s = variant_ext::visit(s, in, out);
    assert(std::holds_alternative<circle>(s));
}
