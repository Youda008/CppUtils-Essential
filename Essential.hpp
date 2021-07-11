//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: declarations that should be built-in features of the languge, but aren't
//======================================================================================================================

#ifndef CPPUTILS_ESSENTIAL_INCLUDED
#define CPPUTILS_ESSENTIAL_INCLUDED


#include <cstdint>
#include <climits>
#include <utility>  // move, forward, swap
#include <type_traits>  // is_same, is_integral, ... (included from utility, can't be avoided)

using uint = unsigned int;
using ushort = unsigned short;
using ulong = unsigned long;
using ullong = unsigned long long;
//using byte = uint8_t;

using std::move;


namespace own {

// C++17
template< typename Container >
constexpr size_t size( const Container & cont ) noexcept
{
	return cont.begin() - cont.end();
}

// In C++11 std::begin and std::end is not constexpr so we have to make a specialization
template< typename ElemType, size_t Size >
constexpr size_t size( const ElemType (&) [Size] ) noexcept
{
	return Size;
}

} // namespace own


// Compiler dependent way to silence unused variable warnings in C++11.
/* If the project is limited to C++11 this is to be used instead of [[maybe_unused]]. This works in gcc and clang.
 * Users of other compilers will have to deal with occasional warnings or disable them with command line argument. */
#ifdef __GNUC__
	#define MAYBE_UNUSED __attribute__((unused))
#else
	#define MAYBE_UNUSED
#endif


#endif // CPPUTILS_ESSENTIAL_INCLUDED
