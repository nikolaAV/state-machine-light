/*
    g++ main.cpp Logic.cpp -std=c++14 -o exe -g
    g++ main.cpp Logic.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
*/

// #define NDEBUG

#include <iostream>
#include <cassert>
#include <tuple>
#include <string_view>

#include "Logic.hpp"

using std::tie;
using std::make_tuple;
using std::string_view;

namespace XYZLogic {

auto tie(OutputData const& v) {
    return tie(v.feature_state, v.position, v.rotation, v.cancelation_flag);
}

bool operator==(OutputData const& left, OutputData const& right) {
    return tie(left) == tie(right);
}

} // namespace XYZLogic


using namespace XYZLogic;

State::Type state;
InputData in;
OutputData out;

int main()
{
    tie(out, state) = logic(in, state);
    assert((out == OutputData{"Off", {}, {}, false}));

    in.enabled = true;
    tie(out, state) = logic(in, state);
    assert((out == OutputData{"Awaiting", {}, {}, false}));

    tie(out, state) = logic(in, state);
    assert((out == OutputData{"Awaiting", {}, {}, false}));

    tie(out, state) = logic(in, state);
    assert((out == OutputData{"Awaiting", {}, {}, false}));

    in.signal1 = 1;
    in.signal2 = 2;
    in.signal3 = 3;
    tie(out, state) = logic(in, state);
    assert(out.feature_state == "On");
    assert(!out.position.empty());
    assert(!out.rotation.empty());
    assert(out.cancelation_flag == false);

    tie(out, state) = logic(in, state);
    assert(out.feature_state == "On");

    tie(out, state) = logic(in, state);
    assert(out.feature_state == "On");

    in.signal1 = 2+3;
    tie(out, state) = logic(in, state);
    assert(out.feature_state == "On");

    tie(out, state) = logic(in, state);
    assert(out.feature_state == "Off");

    tie(out, state) = logic(in, state);
    assert(out.feature_state == "Awaiting");
}
