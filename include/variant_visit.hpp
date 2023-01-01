#ifndef HEADER_GUARD_YAPFHTGYTKEUPMKE
#define HEADER_GUARD_YAPFHTGYTKEUPMKE

#include "variant_cast.hpp"
#include "remove_cvref.hpp"

//
// Applies the visitor vis (Callable that can be called with any type from variant) to the variant var.
// Visitor specification has to provide overload resolution for every type enclosed in variant var
//      with the following signature: func(ValueType v) -> std::variant<any subset of the predefined types>
// @param [in] var std::variant a value storing something from a list of predefined types
// @param [in] vis callable object(s) wich can be applied to any value from var  
// @return std::variant of predefined types (the same as type of var) which contains a value returned by vis
// @code 
//      using OneOf = std::variant<int, double, UserDefined>; // line A: predefined types
//      auto accept(int v) { ...
//      auto accept(double v) { ...
//      auto accept(UserDefined const& v) {
//          std::cout << ...v << std::endl;
//          return OneOf{double};   // <-- any set of types from line A
//      }
//      auto ret = visit(OneOf{UserDefined{...}}, [](v){ return accept(v); });
// @endcode
// @see callable https://en.cppreference.com/w/cpp/named_req/Callable

namespace variant_ext {

template <typename VariantT, typename VisitorT>
auto visit(VariantT&& var, VisitorT&& vis)
{
    return std::visit(
         [&](auto&& v) { return variant_cast<cpp20::remove_cvref_t<VariantT>>(std::forward<VisitorT>(vis)(v)); }
        ,std::forward<VariantT>(var)
    );    
}

} // namespace variant_ext

#endif // HEADER_GUARD_YAPFHTGYTKEUPMKE
