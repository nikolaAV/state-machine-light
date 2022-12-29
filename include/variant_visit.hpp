#ifndef HEADER_GUARD_YAPFHTGYTKEUPMKE
#define HEADER_GUARD_YAPFHTGYTKEUPMKE

#include "variant_cast.hpp"

//
// Dispatches function call in compile time depending on a real underlying value type stored in a variant
// Invoked function specification: accept(ValueType, InputType, OutputType) : std::variant<predefined types...>
// @param [in] var std::variant value storing something from a list of predefined types
// @param [in] in input data of any type 
// @param [out] out output data of any type 
// @return std::variant of predefined types which contains a value returned by the selected 'accept'
// @code 
//      using OneOf = std::variant<int, double, UserDefined>;
//      auto accept(UserDefined const& v, Type1 const& input, Type2& output) {
//          ...
//          return OneOf{...};    
//      }
//      auto ret = visit(OneOf{UserDefined{...}}, input, output);
// @endcode
// @note successful compilation is required 'accept' definition for each predefined types specified in the primary variant

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
