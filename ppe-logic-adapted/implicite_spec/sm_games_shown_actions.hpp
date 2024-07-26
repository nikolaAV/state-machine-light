#ifndef HEADER_GUARD_HSPXBCBSECQXNLQG
#define HEADER_GUARD_HSPXBCBSECQXNLQG

#include "../Data.hpp"                  // InputData
#include "../tfsml/action.hpp"          // primary on_transition_action<....>

#include "sm_games_shown_states.hpp"    // user defined states

namespace tfsml
{

template <typename From, typename To, typename InputData>
To on_transition_action(From const&, InputData const&)
{
    // common case, by default  
    return {}; // EFeatureState::Off for target states
}

template <>
inline CarOn_FirstP on_transition_action<initial, CarOn_FirstP, InputData>(initial const&, InputData const&)
{
    // exept for this one
    return {EFeatureState::On};
}

}   // namespace tfsml

#endif // HEADER_GUARD_HSPXBCBSECQXNLQG
