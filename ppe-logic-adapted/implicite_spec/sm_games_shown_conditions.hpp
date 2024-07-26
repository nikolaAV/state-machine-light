#ifndef HEADER_GUARD_UJOSGOKPHRDWKJSF
#define HEADER_GUARD_UJOSGOKPHRDWKJSF

#include "../DataConditions.hpp"        // isGearPositionParking, isIgnitionOn
#include "../tfsml/condition.hpp"       // primary is_transition_enabled<....>

#include "sm_games_shown_states.hpp"    // user defined states

namespace tfsml
{

template <>
inline bool is_transition_enabled<initial,CarOn_FirstP>(initial const&, InputData const& data)
{
    return isIgnitionOn(data) && isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<initial,CarOn_noP>(initial const&, InputData const& data)
{
    return isIgnitionOn(data) && !isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<initial,CarOff_noP>(initial const&, InputData const& data)
{
    return !isIgnitionOn(data) && !isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<initial,CarOff_P>(initial const&, InputData const& data)
{
    return !isIgnitionOn(data) && isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<CarOn_FirstP,CarOn_noP>(CarOn_FirstP const&, InputData const& data)
{
    return !isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<CarOn_FirstP,CarOff_P>(CarOn_FirstP const&, InputData const& data)
{
    return !isIgnitionOn(data);
}

template <>
inline bool is_transition_enabled<CarOn_noP,CarOff_noP>(CarOn_noP const&, InputData const& data)
{
    return !isIgnitionOn(data);
}

template <>
inline bool is_transition_enabled<CarOn_noP,CarOn_P>(CarOn_noP const&, InputData const& data)
{
    return isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<CarOn_P,CarOn_noP>(CarOn_P const&, InputData const& data)
{
    return !isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<CarOn_P,CarOff_P>(CarOn_P const&, InputData const& data)
{
    return !isIgnitionOn(data);
}

template <>
inline bool is_transition_enabled<CarOff_P,CarOff_noP>(CarOff_P const&, InputData const& data)
{
    return !isGearPositionParking(data);
}

template <>
inline bool is_transition_enabled<CarOff_P,CarOn_FirstP>(CarOff_P const&, InputData const& data)
{
    return isIgnitionOn(data);
}

template <>
inline bool is_transition_enabled<CarOff_noP,CarOn_noP>(CarOff_noP const&, InputData const& data)
{
    return isIgnitionOn(data);
}

template <>
inline bool is_transition_enabled<CarOff_noP,CarOff_P>(CarOff_noP const&, InputData const& data)
{
    return isGearPositionParking(data);
}

} // namespace tfsml

#endif // HEADER_GUARD_UJOSGOKPHRDWKJSF
