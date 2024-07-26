#ifndef HEADER_GUARD_QJBVZMLLEMGRBKZP
#define HEADER_GUARD_QJBVZMLLEMGRBKZP

#include <variant>

#include "transition.hpp"
#include "remove_cvref.hpp"
#include "variant_aux.hpp"

//
// @brief template finite state machine light
// 
namespace tfsml
{

//
// @see https://github.com/nikolaAV/skeleton/tree/master/type_list
// 
template <typename... Ts>
// requires every T is to be tfsml::transition<...>
struct transition_list
{
};

//
// @brief based on transition list, returns a variant of possible target states
// 
template <typename TransitionList>
struct target_states;

template <typename... Ts>
struct target_states<transition_list<Ts...>>
{
    using type = std::variant<typename Ts::to_type...>;
};

template <typename TransitionList>
using target_states_t = typename target_states<TransitionList>::type;

//
// @brief enumerates all transitions in a list 
// and tries to fulfill each of them, one by one in order of their definition in the given state 
// @param from - the current (given) state
// @param data - input data
// @retval variant value of VariantOfStates type, where the current state is replaced with the target state if one from transition list has a place

template <typename VariantOfStates, typename TransitionList>
struct Applying;

template <typename VariantOfStates, typename Head, typename... Tail>
struct Applying<VariantOfStates, transition_list<Head, Tail...>>
{
    template <typename From, typename InputData>
    VariantOfStates operator()(From const& from, InputData const& data)
    {
        return 
            typename Head::condition_type{}(from, data)? 
                typename Head::action_type{}(from, data) :
                Applying<VariantOfStates, transition_list<Tail...>>{}(from, data)
        ;    
    }
};

template <typename VariantOfStates, typename Head>
struct Applying<VariantOfStates, transition_list<Head>>
{
    template <typename From, typename InputData>
    VariantOfStates operator()(From const& from, InputData const& data)
    {
        return 
            typename Head::condition_type{}(from, data)?
                typename Head::action_type{}(from, data) :
                VariantOfStates{from}
        ;
    }
};

//
// @brief tries to fulfill transition from 'from' state to another state
//  where where the another state is determined by a list of outgoing transitions with respect to Input Data 
// @param TransitionList is type list of transitions specified in outgoing transitions section of a user defined state
// @param from - the current state
// @param data - input data
// @retval variant is a type of possible states, where the current state is replaced with the target state if one of transition list can be  achieved
//       otherwise the current state ('from') is a holded value in returned variant
// 
template <typename TransitionList, typename From, typename InputData>
auto fulfill_transition(From const& from, InputData const& data)
{
    using variant_type = variant_aux::push_back_t<target_states_t<TransitionList>,From>;

    return Applying<variant_type, TransitionList>{}(from, data);
}

} // namespace tfsml 


#endif // HEADER_GUARD_QJBVZMLLEMGRBKZP
