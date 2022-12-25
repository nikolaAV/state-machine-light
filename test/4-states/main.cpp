/*
    g++ main.cpp Logic.cpp -std=c++14 -o exe -g
    g++ main.cpp Logic.cpp -std=c++17 -o exe
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
    std::tie(output, state) = logic(input, state);

}
