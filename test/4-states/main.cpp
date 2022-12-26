/*
    g++ main.cpp Logic.cpp -std=c++14 -o exe -g
    g++ main.cpp Logic.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
*/

// #define NDEBUG

#include <iostream>
#include <cassert>
#include <tuple>

#include "Logic.hpp"

using namespace XYZLogic;

State::Type state;
InputData input;
OutputData output;

int main()
{
    // iteration 1
    std::tie(output, state) = logic(input, state);

    // iteration 2
    std::tie(output, state) = logic(input, state);

    // iteration 3
    std::tie(output, state) = logic(input, state);
}
