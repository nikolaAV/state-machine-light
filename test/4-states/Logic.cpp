
#include <type_traits>

#include "Logic.hpp"
#include "../../include/variant_visit.hpp"

namespace XYZLogic {

namespace cpp20 {
template<typename T>
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}   // namespace cpp20

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


template <typename StateT>
using Transition_t = typename StateT::Transition;

#define NEXT_TRANSITION(current_state)   \
      Transition_t<cpp20::remove_cvref_t<decltype(current_state)>>     

using namespace State;

auto accept(Start const& current, InputData const& in, OutputData& out)
{
    auto const processEnabled = [&] {
        out.feature_state = "Awaiting";
        return Idle { makeRequest(in) };
    }; 
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Start {};
    }; 

    using transition = NEXT_TRANSITION(current);
    return 
        in.enabled ?
            transition{processEnabled()} :
            transition{processDisabled()}
    ;
}

auto accept(Idle const& current, InputData const& in, OutputData& out)
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

    using transition = NEXT_TRANSITION(current);
    return 
        !in.enabled ?
            transition{processDisabled()} :
        isAwaiting(in) ?
            transition{processIdle()} :
            transition{processAnimation()}
    ;
}

auto accept(Showing const& current, InputData const& in, OutputData& out)
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

    using transition = NEXT_TRANSITION(current);
    return 
        !in.enabled ?
            transition{processDisabled()} :
        in.signal1 < in.signal2 + in.signal3 ?
            transition{processInterrupted()} :
        in.signal1 > in.signal2 + in.signal3 ?
            transition{processAnimation()} :
            transition{processFinish()}     // case: in.signal1 == in.signal2 + in.signal3
    ;
}

auto accept(Stop const& current, InputData const&, OutputData& out)
{
    out.feature_state = "Off";
    out.cancelation_flag = transform(current);

    using transition = NEXT_TRANSITION(current);
    return transition{Start{}};
}
LogicResult logic(InputData const& in, State::Type const& state)
{
    OutputData out;
    return {
         std::move(out)                     // <-- reference to output
        ,variant_ext::visit(state, in, out) // <-- new state
    };
}

} // namespace XYZLogic
