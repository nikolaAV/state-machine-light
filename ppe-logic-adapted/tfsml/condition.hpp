#ifndef HEADER_GUARD_WLNNBDRHSGUDWCTH
#define HEADER_GUARD_WLNNBDRHSGUDWCTH

//
// @brief template finite state machine light
// 
namespace tfsml
{
    //
    // @brief generic incomplete condition stub for name resolution during template instantiation
    // Client code is responsible to provide specialization for all combinations
    // state 'From' --> 'To' described in outgoing transitions section of user defined state
    //
    template <typename From, typename To, typename InputData>
    bool is_transition_enabled(From const&, InputData const& );

    //
    // @brief expectation by default, 'is_transition_enabled<From,To>(...)' specialization should be defined on client side
    // 
    template <typename From, typename To>
    struct condition
    {
        template <typename InputData>
        bool operator()(From const& from, InputData const& data) const
        {
            return is_transition_enabled<From,To>(from, data);
        }
    };

} // namespace tfsml 

#endif // HEADER_GUARD_WLNNBDRHSGUDWCTH
