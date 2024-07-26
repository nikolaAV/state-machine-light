
#ifndef HEADER_GUARD_ZFACIIPAXZNDYPHY
#define HEADER_GUARD_ZFACIIPAXZNDYPHY

#include <variant>
#include <utility>
#include <typeinfo>     // typeid(expr).name()

//
// @brief template finite state machine light
// 
namespace tfsml
{

namespace variant_aux
{

//
// @brief cast variant type to another variant type, if it's possible
// Restricted variant is allowed to be assignable to the primary variant,
// if the restricted contains a subset of types from a list which composes the primary one.
// This is very similar to relationship 'base-derived' in OOP
// @param Output - primary variant
// @param Input - restricted variant (containing subset of types from the primary variant)
// @code 
//     using Primary = std::variant<std::string,int,double>; 
//     using Specific = std::variant<double, int>; 
//     Primary p = variant_aux::cast<Primary>(Specific{3.14}); - Ok
//
//     using Incompliant = std::variant<std::string,int,double,char>;
//     Primary p = variant_aux::cast<Primary>(Incompliant{3.14}); - Compile error: no match for operator=(Primary&, char) 
// @endcode


template <typename Output, typename Input>
Output cast(Input&& in)
{
    Output out;
    std::visit(
         [&out](auto&& v){out = std::forward<decltype(v)>(v);}
        ,std::forward<Input>(in)
    );    
    return out;
}

//
// @brief variant<T1,T2,T3> + T4 = variant<T1,T2,T3,T4>
// 
template <typename Variant, typename T>
struct push_back;

template <typename U, typename... Ts>
struct push_back<std::variant<Ts...>, U>
{
    using type = std::variant<Ts..., U>;
};

template <typename Variant, typename T>
using push_back_t = typename push_back<Variant, T>::type;

//
// @brief name of type which the variant currently holds
// 
template <typename... Ts>
char const* holds_type_name(std::variant<Ts...> const& v)
{
    return std::visit([](auto&& type) {return typeid(type).name(); } ,v);
}

} // namespace variant_aux


} // namespace tfsml 

#endif // HEADER_GUARD_ZFACIIPAXZNDYPHY
