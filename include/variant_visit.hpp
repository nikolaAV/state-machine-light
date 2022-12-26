#ifndef HEADER_GUARD_YAPFHTGYTKEUPMKE
#define HEADER_GUARD_YAPFHTGYTKEUPMKE

#include "variant_cast.hpp"

//
// Dispatches function call depending on a real underlying value type stored in a variant
// Invoked function specification: accept(ValueType, InputType, OutputType) : std::variant<predefined types...>
// @param [in] var std::variant value storing something from a list of predefined types
// @param [in] in input data of any type 
// @param [out] in output data of any type 
// @return std::variant of predefined types
// @code 
//      using OneOf = std::variant<int, double, UserDefined>;
//      auto accept(UserDefined const& v, Type1 const& input, Type2& output) {
//          ...
//          return OneOf{...};    
//      }
//      auto ret = visit(OneOf{UserDefined{...}}, input, output);
// @endcode

namespace variant_ext {

template <typename InputT, typename OutputT, typename... Ts>
auto visit(std::variant<Ts...>const & var, InputT const& in, OutputT& out)
{
    return std::visit(
         [&](auto&& underlying){ return variant_cast<std::variant<Ts...>>(accept(underlying, in, out)); }
        ,var
    );    
}

} // namespace variant_ext

#endif // HEADER_GUARD_YAPFHTGYTKEUPMKE
