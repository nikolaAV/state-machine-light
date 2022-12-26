#ifndef HEADER_GUARD_KEFMFOPUMWXIJZMU
#define HEADER_GUARD_KEFMFOPUMWXIJZMU

#include <variant>
#include <utility>

//
// Restricted variant is allowed to be assignable to the primary variant,
// if the restricted contains a subset of types from a list which composes the primary one.
// This is very similar to relationship 'base-derived' in OOP
// @code 
//     using Primary = std::variant<std::string,int,double>; 
//     using Specific = std::variant<double, char>; 
//     Primary p = variant_cast<Primary>(Specific{3.14}); - Ok
//     Primary p = variant_cast<Primary>(Specific{'A'}); - exception: bad_variant_access in run-time
// @endcode

namespace variant_ext {

template <typename Output, typename Input>
Output variant_cast(Input&& in)
{
    Output out;
    std::visit(
         [&out](auto&& v){out = std::forward<decltype(v)>(v);}
        ,std::forward<Input>(in)
    );    
    return out;
}

} // namespace variant_ext

#endif // HEADER_GUARD_KEFMFOPUMWXIJZMU
