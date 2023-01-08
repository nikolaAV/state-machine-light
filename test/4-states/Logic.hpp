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
    std::string feature_state {"Off"};
    std::vector<double> position;
    std::vector<double> rotation;
    bool cancelation_flag {false};
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
    using Transition = OneOf<Start, Idle>;
};

struct Idle
{
    using Transition = OneOf<Start, Showing, Idle>;

    std::uint32_t request_id;
};

struct Showing
{
    using Transition = OneOf<Showing, Stop>;

    std::uint32_t duration;
    std::string text;
};

struct Stop
{
    using Transition = OneOf<Start>;

    std::uint32_t error_code;
    double  result;
};

using Type = OneOf<Start, Idle, Showing, Stop>;

}   // namespace State


using LogicResult = std::pair<OutputData, State::Type>;

LogicResult logic(InputData const&, State::Type const&);

}   // namespace XYZLogic

