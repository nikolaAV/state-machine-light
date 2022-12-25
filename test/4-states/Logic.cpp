
#include "Logic.hpp"
#include "../../include/variant_cast.hpp"

namespace XYZLogic {

namespace {

constexpr auto c_success = std::uint32_t{0};
constexpr auto c_error_disabled = std::uint32_t{1};

bool isAwaiting(InputData const& in)
{
    // ....
    return {};
}

uint32_t makeRequest(InputData const& in)
{
    // ....
    return {};
}

uint32_t updateRequest(InputData const& in, uint32_t previous)
{
    // ....
    return {};
}

std::vector<double> calculatePosition(InputData const& in)
{
    // ....
    return {};
}

std::vector<double> calculateRotation(InputData const& in)
{
    // ....
    return {};
}

uint32_t getDuration(InputData const& in)
{
    // ....
    return {};
}

std::string getText(InputData const& in)
{
    // ....
    return {};
}

uint32_t getError(InputData const& in, std::uint32_t duration)
{
    // ....
    return {};
}

double getResult(InputData const& in, std::string const& text)
{
    // ....
    return {};
}

bool transform(State::Stop const& data)
{
    // ...
    return {};
}

}   // end of anonymous namespace

using namespace State;

OneOf<Start, Idle> Start::accept(InputData const& in, OutputData& out) const
{
    auto const processEnabled = [&] {
        out.feature_state = "Awaiting";
        return Idle { makeRequest(in) };
    }; 
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Start {};
    }; 

    using TransitionType = OneOf<Start, Idle>;
    return 
        in.enabled ?
            TransitionType{processEnabled()} :
            TransitionType{processDisabled()}
    ;
}

OneOf<Start, Showing, Idle> Idle::accept(InputData const& in, OutputData& out) const
{
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Start {};
    }; 
    auto const processIdle = [&] {
        out.feature_state = "Awaiting";
        return Idle { updateRequest(in, this->request_id)};
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

    using TransitionType = OneOf<Start, Showing, Idle>;
    return 
        !in.enabled ?
            TransitionType{processDisabled()} :
        isAwaiting(in) ?
            TransitionType{processIdle()} :
            TransitionType{processAnimation()}
    ;
}

OneOf<Showing, Stop> Showing::accept(InputData const& in, OutputData& out) const
{
    auto const processDisabled = [&] {
        out.feature_state = "Off";
        return Stop { c_error_disabled, {}};
    }; 
    auto const processInterrupted = [&] {
        out.feature_state = "Off";
        return Stop { getError(in, this->duration), {}};
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
        return Stop { c_success, getResult(in, this->text)};
    }; 

    using TransitionType = OneOf<Showing, Stop>;
    return 
        !in.enabled ?
            TransitionType{processDisabled()} :
        in.signal1 < in.signal2 + in.signal3 ?
            TransitionType{processInterrupted()} :
        in.signal1 > in.signal2 + in.signal3 ?
            TransitionType{processAnimation()} :
            TransitionType{processFinish()}     // case: in.signal1 == in.signal2 + in.signal3
    ;
}

OneOf<Start> Stop::accept(InputData const& in, OutputData& out) const
{
    out.feature_state = "Off";
    out.cancelation_flag = transform(*this);
    return Start{};
}

LogicResult logic(InputData const& in, State::Type const& state)
{
    using namespace variant_ext;

    OutputData out;
    State::Type new_state;
    std::visit(
         [&](auto&& underlying){ new_state = variant_cast<State::Type>(underlying.accept(in, out)); }
        ,state
    );    
    return {std::move(out), std::move(new_state)};
}

} // namespace XYZLogic
