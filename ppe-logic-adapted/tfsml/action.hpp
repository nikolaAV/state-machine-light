#ifndef HEADER_GUARD_XSUDKAVLKWKJTXJL
#define HEADER_GUARD_XSUDKAVLKWKJTXJL

//
// @brief template finite state machine light
// 
namespace tfsml
{
    //
    // @brief generic incomplete action stub for name resolution during template instantiation
    // Client code is responsible to provide specialization for all combinations
    // state 'From' --> 'To' described in outgoing transitions section of user defined state
    //
    template <typename From, typename To, typename InputData>
    To on_transition_action(From const&, InputData const&);

    //
    // @brief expectation by default, 'on_transition_action<From,To>(...)' specialization should be defined on client side
    // 
    template <typename From, typename To>
    struct action
    {
        template <typename InputData>
        To operator()(From const& from, InputData const& data) const
        {
            return on_transition_action<From, To>(from, data);
        }
    };

} // namespace tfsml 

#endif // HEADER_GUARD_XSUDKAVLKWKJTXJL
