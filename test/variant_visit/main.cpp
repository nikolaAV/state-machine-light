/*
    g++ main.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
*/

#include <cassert>
#include <iostream>

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

shape accept(circle const&) {
    std::cout << "circle --> square" << std::endl;
    return square{};
}

auto accept(square const&) {
    std::cout << "square --> triangle" << std::endl;
    return std::variant<triangle>{};
}

auto accept(triangle const&) {
    std::cout << "triangle --> rectangle" << std::endl;
    return std::variant<rectangle>{rectangle{1 ,2}}; 
}

shape accept(rectangle const&) {
    std::cout << "rectangle --> circle" << std::endl;
    return circle{3.1456};
}

auto next(shape const& s) {
    return variant_ext::visit(s, [](auto&& v){ return accept(v); });
}

template <typename T>
bool is_type_of(shape const& s) {
    return std::holds_alternative<T>(s);
}

int main()
{
    shape s;

    assert(is_type_of<circle>(s));

    s = next(s);
    assert(is_type_of<square>(s));

    s = next(s);
    assert(is_type_of<triangle>(s));

    s = next(s);
    assert(is_type_of<rectangle>(s));

    s = next(s);
    assert(is_type_of<circle>(s));
}
