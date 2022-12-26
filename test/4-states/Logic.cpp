
#include "Logic.hpp"
#include "../../include/variant_visit.hpp"

namespace XYZLogic {

namespace {

constexpr auto c_success = std::uint32_t{0};
constexpr auto c_error_disabled = std::uint32_t{1};

bool isAwaiting(InputData const& in) {
    (void)in; // ....
    return {};
}

uint32_t makeRequest(InputData const& in) {
    (void)in; // ....
    return {};
}

uint32_t updateRequest(InputData const& in, uint32_t previous) {
    (void)in; (void)previous; // ....
    return {};
}

std::vector<double> calculatePosition(InputData const& in) {
    (void)in; // ....
    return {};
}

std::vector<double> calculateRotation(InputData const& in) {
    (void)in; // ....
    return {};
}

uint32_t getDuration(InputData const& in) {
    (void)in; // ....
    return {};
}

std::string getText(InputData const& in) {
    (void)in; // ....
    return {};
}

uint32_t getError(InputData const& in, std::uint32_t duration) {
    (void)in; (void)duration; // ....
    return {};
}

double getResult(InputData const& in, std::string const& text) {
    (void)in; (void)text; // ....
    return {};
}

bool transform(State::Stop const& data) {
    (void)data; // ...
    return {};
}

}   // end of anonymous namespace

using namespace State;

template <typename StateT>
using Transition_t = typename StateT::Transition;

Transition_t<Start> accept(Start const&, InputData const& in, OutputData& out)
{
    auto const processEnabled = [&] {
        out.feature_state = "Awaiting";
        return Idle { makeRequest(in) };
    }; 
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Start {};
    }; 

    using ret_t = Transition_t<Start>;
    return 
        in.enabled ?
            ret_t{processEnabled()} :
            ret_t{processDisabled()}
    ;
}

Transition_t<Idle> accept(Idle const& current, InputData const& in, OutputData& out)
{
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Start {};
    }; 
    auto const processIdle = [&] {
        out.feature_state = "Awaiting";
        return Idle { updateRequest(in, current.request_id)};
    }; 
    auto const processAnimation = [&] {
        out.feature_state = "On";
        out.position = calculatePosition(in);
        out.rotation = calculateRotation(in);
        return Showing {
             getDuration(in)
            ,getText(in)  
        };
    }; 

    using ret_t = Transition_t<Idle>;
    return 
        !in.enabled ?
            ret_t{processDisabled()} :
        isAwaiting(in) ?
            ret_t{processIdle()} :
            ret_t{processAnimation()}
    ;
}

Transition_t<Showing> accept(Showing const& current, InputData const& in, OutputData& out)
{
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Stop { c_error_disabled, {}};
    }; 
    auto const processInterrupted = [&] {
        out.feature_state = "Off";
        return Stop { getError(in, current.duration), {}};
    }; 
    auto const processAnimation = [&] {
        out.feature_state = "On";
        out.position = calculatePosition(in);
        out.rotation = calculateRotation(in);
        return Showing {
             getDuration(in)
            ,getText(in)  
        };
    }; 
    auto const processFinish = [&] {
        out.feature_state = "On";
        return Stop { c_success, getResult(in, current.text)};
    }; 

    using ret_t = Transition_t<Showing>;
    return 
        !in.enabled ?
            ret_t{processDisabled()} :
        in.signal1 < in.signal2 + in.signal3 ?
            ret_t{processInterrupted()} :
        in.signal1 > in.signal2 + in.signal3 ?
            ret_t{processAnimation()} :
            ret_t{processFinish()}     // case: in.signal1 == in.signal2 + in.signal3
    ;
}

Transition_t<Stop> accept(Stop const& current, InputData const&, OutputData& out)
{
    out.feature_state = "Off";
    out.cancelation_flag = transform(current);
    return Start{};
}
LogicResult logic(InputData const& in, State::Type const& state)
{
    using namespace variant_ext;

    using namespace variant_ext;
    OutputData out;
    return { std::move(out), visit(state, in, out)};
}

} // namespace XYZLogic
