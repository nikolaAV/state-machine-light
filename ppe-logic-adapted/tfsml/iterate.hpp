#ifndef HEADER_GUARD_ECITRFXCDGCADCUO
#define HEADER_GUARD_ECITRFXCDGCADCUO

#include <variant>

#include "remove_cvref.hpp"
#include "variant_aux.hpp"

//
// @brief template finite state machine light
// 
namespace tfsml
{

//
// @brief transform var_of_states (active:state A) --> var_of_states (active:state B) depends on input data
// 
template <typename InputData, typename... Ts>
// requires 
//  - every T in parameter pack 'Ts' is an user defined type of particular state
//  - InputData is an user defined type of input data
auto iterate(InputData const& data, std::variant<Ts...> const& var_of_states)
{
    auto visitor = [&data](auto&& state)
    {
        using pure_from_state_type = cpp14::remove_cvref_t<decltype(state)>;
        using transitions_type = typename pure_from_state_type::outgoing_transitions;
        using pure_variant_type = cpp14::remove_cvref_t<decltype(var_of_states)>;

        return variant_aux::cast<pure_variant_type>(fulfill_transition<transitions_type>(state, data));
    };

    return std::visit(visitor, var_of_states);
}

} // namespace tfsml 


#endif // HEADER_GUARD_ECITRFXCDGCADCUO
