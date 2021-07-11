//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: template helpers, generic container helpers and backports from newer C++ standards
//======================================================================================================================

#ifndef CPPUTILS_LANGUAGE_INCLUDED
#define CPPUTILS_LANGUAGE_INCLUDED


#include "Essential.hpp"

#include "Span.hpp"

#include <iterator>  // advance, begin, end


namespace own {


//----------------------------------------------------------------------------------------------------------------------
//  things backported from C++ standards newer than C++11

// C++14
template< typename Iter >
constexpr std::reverse_iterator<Iter> make_reverse_iterator( Iter i ) noexcept
{
    return std::reverse_iterator<Iter>(i);
}


//----------------------------------------------------------------------------------------------------------------------
//  container helpers

/// return value variant of std::advance
template< typename Iterator, typename Distance >
Iterator advance( Iterator it, Distance n )
{
	std::advance( it, n );
	return it;
}


//----------------------------------------------------------------------------------------------------------------------
//  scope guards

template< typename EndFunc >
class scope_guard
{
	EndFunc _atEnd;
 public:
	scope_guard( const EndFunc & endFunc ) : _atEnd( endFunc ) {}
	scope_guard( EndFunc && endFunc ) : _atEnd( move(endFunc) ) {}
	~scope_guard() noexcept { _atEnd(); }
};

template< typename EndFunc >
scope_guard< EndFunc > at_scope_end_do( const EndFunc & endFunc )
{
	return scope_guard< EndFunc >( endFunc );
}

template< typename EndFunc >
scope_guard< EndFunc > at_scope_end_do( EndFunc && endFunc )
{
	return scope_guard< EndFunc >( move(endFunc) );
}


//----------------------------------------------------------------------------------------------------------------------
//  type traits helpers

/// Determines types that are convertible to integer and serializable to network stream.
template< typename Type >
struct is_int_or_enum : public std::integral_constant< bool, std::is_integral<Type>::value || std::is_enum<Type>::value > {};

/// For integer it returns the integer and for enum it returns its underlying_type.
// https://stackoverflow.com/questions/56972288/metaprogramming-construct-that-returns-underlying-type-for-an-enum-and-integer-f
template< typename Type >
struct int_type {
	using type = typename std::conditional<
		/*if*/ std::is_enum<Type>::value,
		/*then*/ std::underlying_type<Type>,
		/*else*/ std::enable_if< std::is_integral<Type>::value, Type >
	>::type::type;
};

/// Correctly converts an enum value to its underlying integer type.
template< typename EnumType >
typename std::underlying_type< EnumType >::type enumToInt( EnumType num ) noexcept
{
	return static_cast< typename std::underlying_type< EnumType >::type >( num );
}


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_LANGUAGE_INCLUDED
