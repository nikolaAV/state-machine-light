
#ifndef HEADER_GUARD_UHABWNROMXKOGBTY
#define HEADER_GUARD_UHABWNROMXKOGBTY

//
// @brief template finite state machine light
// 
namespace tfsml
{

//
// @brief C++17 The overload Pattern adaptation to C++14
// @see https://www.cppstories.com/2019/02/2lines3featuresoverload.html/
//
namespace cpp14 {

template <typename T, typename... Ts>
struct overloaded : T, overloaded<Ts...> 
{
    using T::operator();
    using overloaded<Ts...>::operator();
};
    
template <typename T> struct overloaded<T> : T 
{
    using T::operator();
};

template <typename... Ts>
auto make_overloaded(Ts&&... t) 
{
    return overloaded<Ts...>{std::forward<Ts>(t)...};
}

}   // namespace cpp14

} // namespace tfsml 


#endif // HEADER_GUARD_UHABWNROMXKOGBTY
