#ifndef HEADER_GUARD_VYYUOIBKLHRJMJQQ
#define HEADER_GUARD_VYYUOIBKLHRJMJQQ

#include <variant>

#include "../FeatureState.hpp"
#include "sm_games_shown_type_adaptors.hpp"

struct initial;
struct CarOn_FirstP;
struct CarOn_noP;
struct CarOn_P;
struct CarOff_P;
struct CarOff_noP;

struct initial
{
    using outgoing_transitions = transition_list_t<initial
        ,CarOn_FirstP
        ,CarOn_noP
        ,CarOff_noP
        ,CarOff_P
    >;
};

struct CarOn_FirstP 
{
    // data 
    // @todo, for this particular sm,can be defined as compile time constant
    // but a solution below has been done for demonstration how 'actions<from, to>' work 
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = transition_list_t<CarOn_FirstP
        ,CarOn_noP
        ,CarOff_P
    >;
};

struct CarOn_noP 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = transition_list_t<CarOn_noP
        ,CarOff_noP
        ,CarOn_P
    >;
};

struct CarOn_P 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = transition_list_t<CarOn_P
        ,CarOn_noP
        ,CarOff_P
    >;
};

struct CarOff_P 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = transition_list_t<CarOff_P
        ,CarOff_noP
        ,CarOn_FirstP
    >;
};

struct CarOff_noP 
{
    // data
    EFeatureState feature_state{EFeatureState::Off};

    // outgoing_transitions
    using outgoing_transitions = transition_list_t<CarOff_noP
        ,CarOn_noP
        ,CarOff_P
    >;
};

using GamesShownState = std::variant<initial, CarOn_FirstP, CarOn_noP, CarOn_P, CarOff_P, CarOff_noP>;


#endif // HEADER_GUARD_VYYUOIBKLHRJMJQQ
