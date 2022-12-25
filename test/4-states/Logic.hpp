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
    std::string feature_state = "Off";
    std::vector<double> position;
    std::vector<double> rotation;
    bool cancelation_flag;
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
    auto accept(InputData const&, OutputData&) const -> OneOf<Start, Idle>;
};

struct Idle 
{
    // members
    std::uint32_t request_id;

    // transition
    auto accept(InputData const&, OutputData&) const -> OneOf<Start, Showing, Idle>;
};

struct Showing 
{
    // members
    std::uint32_t duration;
    std::string text;

    // transition
    auto accept(InputData const&, OutputData&) const -> OneOf<Showing, Stop>;
};

struct Stop 
{
    // members
    std::uint32_t error_code;
    double  result;

    // transition
    auto accept(InputData const&, OutputData&) const -> OneOf<Start>;
};

using Type = OneOf<Start, Idle, Showing, Stop>;

}   // namespace State


using LogicResult = std::pair<OutputData, State::Type>;

LogicResult logic(InputData const&, State::Type const&);

}   // namespace XYZLogic

