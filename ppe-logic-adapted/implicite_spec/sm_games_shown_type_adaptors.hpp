#ifndef HEADER_GUARD_FVOLEHFWANNQXLLR
#define HEADER_GUARD_FVOLEHFWANNQXLLR

#include "../tfsml/transition_list.hpp"

template <typename From, typename... Targets>
struct transition_list
{
    using type = tfsml::transition_list<tfsml::transition<From, Targets>...>;
}; 

template <typename From, typename... Targets>
using transition_list_t = typename transition_list<From, Targets...>::type;

#endif // HEADER_GUARD_FVOLEHFWANNQXLLR
