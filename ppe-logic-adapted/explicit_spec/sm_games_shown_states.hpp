#ifndef HEADER_GUARD_VYYUOIBKLHRJMJQQ
#define HEADER_GUARD_VYYUOIBKLHRJMJQQ

#include <variant>

#include "../FeatureState.hpp"
#include "../DataConditions.hpp"
#include "sm_games_shown_type_adaptors.hpp"

struct initial;
struct CarOn_FirstP;
struct CarOn_noP;
struct CarOn_P;
struct CarOff_P;
struct CarOff_noP;

struct initial
{
    using outgoing_transitions = tfsml::transition_list<
         transition_t<initial, CarOn_FirstP,   AND< IF<isIgnitionOn>,          IF<isGearPositionParking>>,     ON  >
        ,transition_t<initial, CarOn_noP,      AND< IF<isIgnitionOn>,      NOT<IF<isGearPositionParking>>>,    OFF >
        ,transition_t<initial, CarOff_noP,     AND< NOT<IF<isIgnitionOn>>, NOT<IF<isGearPositionParking>>>,    OFF >
        ,transition_t<initial, CarOff_P,       AND< NOT<IF<isIgnitionOn>>,     IF<isGearPositionParking>>,     OFF >
    >;
};

struct CarOn_FirstP 
{
    // data 
    // @todo, for this particular sm,can be defined as compile time constant
    // but a solution below has been done for demonstration how 'actions<from, to>' work 
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = tfsml::transition_list<
         transition_t<CarOn_FirstP, CarOn_noP, NOT<IF<isGearPositionParking>>,  OFF>
        ,transition_t<CarOn_FirstP, CarOff_P,  NOT<IF<isIgnitionOn>>,           OFF>
    >;
};

struct CarOn_noP 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = tfsml::transition_list<
         transition_t<CarOn_noP, CarOff_noP,    NOT<IF<isIgnitionOn>>,          OFF>
        ,transition_t<CarOn_noP, CarOn_P,           IF<isGearPositionParking>,  OFF>   

    >;
};

struct CarOn_P 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = tfsml::transition_list<
         transition_t<CarOn_P, CarOn_noP, NOT<IF<isGearPositionParking>>,   OFF>
        ,transition_t<CarOn_P, CarOff_P,  NOT<IF<isIgnitionOn>>,            OFF>

    >;
};

struct CarOff_P 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = tfsml::transition_list<
         transition_t<CarOff_P, CarOff_noP,     NOT<IF<isGearPositionParking>>, OFF>
        ,transition_t<CarOff_P, CarOn_FirstP,       IF<isIgnitionOn>,           ON >
    >;
};

struct CarOff_noP 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = tfsml::transition_list<
         transition_t<CarOff_noP, CarOn_noP,       IF<isIgnitionOn>,            OFF>
        ,transition_t<CarOff_noP, CarOff_P,       IF<isGearPositionParking>,    OFF>

    >;
};

using GamesShownState = std::variant<initial, CarOn_FirstP, CarOn_noP, CarOn_P, CarOff_P, CarOff_noP>;


#endif // HEADER_GUARD_VYYUOIBKLHRJMJQQ
