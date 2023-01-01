#ifndef HEADER_GUARD_WXIXWVQZSOUZNGBI
#define HEADER_GUARD_WXIXWVQZSOUZNGBI
#include <type_traits>

// combines std::remove_cv and std::remove_reference
// @note provided by STL since C++20  
// @see https://en.cppreference.com/w/cpp/types/remove_cvref

namespace cpp20 {

template<typename T>
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}   // namespace cpp20

#endif // HEADER_GUARD_WXIXWVQZSOUZNGBI
