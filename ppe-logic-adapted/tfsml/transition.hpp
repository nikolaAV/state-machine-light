#ifndef HEADER_GUARD_KQAYSPYHRYRGQJMS
#define HEADER_GUARD_KQAYSPYHRYRGQJMS

#include "action.hpp"
#include "condition.hpp"

//
// @brief template finite state machine light
// 
namespace tfsml
{

// 
// @brief transition descriptor
// @param From is a user defined type representing the current state
// @param To is a user defined type representing the target state  
// @param Condition is a user defined type that meets concept 'collable' to give an answer if the given transition is allowed or not
// @param Action what has to be done to fulfill transition 'From' -> 'To'
//  

template <typename From, typename To, typename Condition = condition<From, To>, typename Action = action<From, To>>
struct transition 
{
    using from_type = From;
    using to_type = To;
    using condition_type = Condition;   // signature: 'bool (From const&, T const&) const', where T is an any user defined type (e.g. Input::Data)
    using action_type = Action;         // signature: 'To (From const&, T const&)', where T is an any user defined type (e.g. Input::Data)
};

} // namespace tfsml 


#endif // HEADER_GUARD_KQAYSPYHRYRGQJMS
