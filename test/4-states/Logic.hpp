#include <variant>
#include <string>
#include <vector>

namespace XYZLogic {

struct InputData
{
    bool enabled;
    int signal1;
    int signal2;
    int signal3;
    std::string signal4; 
};

struct OutputData
{
    std::string feature_state;
    std::vector<double> position;
    std::vector<double> rotation;
};

namespace State {

template <typename... T>
using OneOf = std::variant<T...>;

struct Start;
struct Idle;
struct Showing;
struct Stop;

struct Start 
{
    // members

    // transition
    auto accept(InputData const&, OutputData&) -> OneOf<Idle>;
};

struct Idle 
{
    // members
    std::uint32_t id;

    // transition
    auto accept(InputData const&, OutputData&) -> OneOf<Showing, Idle>;
};

struct Showing 
{
    // members
    std::uint32_t duration;
    std::string text;

    // transition
    auto accept(InputData const&, OutputData&) -> OneOf<Showing, Stop>;
};

struct Stop 
{
    // members
    std::uint32_t error_code;
    double  result;

    // transition
    auto accept(InputData const&, OutputData&) -> OneOf<Start>;
};

using Type = OneOf<Start, Idle, Showing, Stop>;

}   // namespace State


using LogicResult = std::pair<OutputData, State::Type>;

LogicResult logic(InputData const&, State::Type);

}   // namespace XYZLogic

