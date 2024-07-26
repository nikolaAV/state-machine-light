#ifndef HEADER_GUARD_CBQYRDWPIRZPAQJI
#define HEADER_GUARD_CBQYRDWPIRZPAQJI


//
// @brief template finite state machine light
// 
namespace tfsml
{

//
// @brief combines std::remove_cv and std::remove_reference
// @note provided by STL since C++20  
// @see https://en.cppreference.com/w/cpp/types/remove_cvref
//
namespace cpp14 {

template<typename T>
struct remove_cvref 
{
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}   // namespace cpp14

} // namespace tfsml 


#endif // HEADER_GUARD_CBQYRDWPIRZPAQJI
