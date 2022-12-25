/*
    g++ main.cpp -std=c++14 -o exe -g
    g++ main.cpp -std=c++17 -o exe
*/

// #define NDEBUG

#include <cassert>
#include <iostream>
#include <variant>

namespace State {

struct Start;
struct Idle;
struct Showing;
struct Stop;

struct Start 
{
    // members


    // transition
    template <typename Input, typename Output>
    auto accept(Input const&, Output&) -> std::variant<Idle>;
};

struct Idle 
{
    // members
    std::uint32_t id;

    // transition
    template <typename Input, typename Output>
    auto accept(Input const&, Output&) -> std::variant<Showing, Idle>;

};

struct Showing 
{
    // members
    std::uint32_t duration;
    std::string text;

    // transition
    template <typename Input, typename Output>
    auto accept(Input const&, Output&) -> std::variant<Showing, Stop>;
};


struct Stop 
{
    // members
    std::uint32_t error_code;
    double  result;

    // transition
    template <typename Input, typename Output>
    auto accept(Input const&, Output&) -> std::variant<Start>;

};

using Type = std::variant<Start, Idle, Showing, Stop>;

}   // namespace State


////////////////////////////////////////////////////


struct InputData
{

};

struct OutputData
{

};

template <typename Restricted, typename Common>
void copy(Restricted const& source, Common& destination)
{
    std::visit([&destination](auto&& v){destination = v;},source);    
}


int main()
{
    State::Type instance;
    std::variant<State::Showing, State::Stop> xxx;

    // instance = xxx;
    copy(xxx, instance);

    assert(!"Hello, Nikola");
    std::cout << "Hello, Nikola" << std::endl;
}
