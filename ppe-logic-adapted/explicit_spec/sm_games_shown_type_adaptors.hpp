#ifndef HEADER_GUARD_FVOLEHFWANNQXLLR
#define HEADER_GUARD_FVOLEHFWANNQXLLR

#include "../Data.hpp"                  // InputData
#include "../tfsml/transition_list.hpp"

template <bool(*Func)(InputData const&)>
struct IF
{
    template <typename From>
    bool operator()(From const&, InputData const& data) const
    {
        return Func(data);
    }
};

template <typename Cond1, typename Cond2>
// requires Cond1 and Cond2 are IF<...> instantiations
struct AND
{
    template <typename From>
    bool operator()(From const& dummy, InputData const& data) const
    {
        return Cond1{}(dummy, data) && Cond2{}(dummy, data);
    }
};

template <typename Cond>
// requires Cond is IF<...> instantiation
struct NOT
{
    template <typename From>
    bool operator()(From const& dummy, InputData const& data) const
    {
        return !Cond{}(dummy, data);
    }
};

template <typename To>
struct OFF
{
    template <typename From>
    To operator()(From const&, InputData const&) const
    {
        return {}; // EFeatureState::Off for default
    }
};

template <typename To>
struct ON
{
    template <typename From>
    To operator()(From const&, InputData const&) const
    {
        return {EFeatureState::On};
    }
};

template <typename From, typename To, typename Condition, template <class> class Action>  
struct transition
{
    using type = tfsml::transition<From, To, Condition, Action<To>>; 
};

template <typename From, typename To, typename Condition, template <class> class Action>  
using transition_t = typename transition<From, To, Condition, Action>::type;


#endif // HEADER_GUARD_FVOLEHFWANNQXLLR
