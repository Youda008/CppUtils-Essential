//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Created on:  1.11.2020
// Description: language-specific utils
//======================================================================================================================

#ifndef CPPUTILS_LANGUAGE_INCLUDED
#define CPPUTILS_LANGUAGE_INCLUDED


#include "Essential.hpp"


namespace own {


//----------------------------------------------------------------------------------------------------------------------

// std::size is C++17, and since we want to support C++11 we have to make our own
template< typename Container >
constexpr size_t size( const Container & cont )
{
	return std::end(cont) - std::begin(cont);
}


//----------------------------------------------------------------------------------------------------------------------

template< typename EndFunc >
class scope_guard
{
	EndFunc _atEnd;
 public:
	scope_guard( const EndFunc & endFunc ) : _atEnd( endFunc ) {}
	~scope_guard() { _atEnd(); }
};

template< typename EndFunc >
scope_guard< EndFunc > at_scope_end_do( const EndFunc & endFunc )
{
	return scope_guard< EndFunc >( endFunc );
}


//----------------------------------------------------------------------------------------------------------------------

/// this determines types that are convertible to integer and serializable to network stream
template< typename Type >
struct is_int_or_enum : public std::integral_constant< bool, std::is_integral<Type>::value || std::is_enum<Type>::value > {};

/// for integer it returns the integer, and for enum it returns its underlying_type
// https://stackoverflow.com/questions/56972288/metaprogramming-construct-that-returns-underlying-type-for-an-enum-and-integer-f
template< typename Type >
struct int_type {
	using type = typename std::conditional<
		/*if*/ std::is_enum<Type>::value,
		/*then*/ std::underlying_type<Type>,
		/*else*/ std::enable_if< std::is_integral<Type>::value, Type >
	>::type::type;
};

/// correctly converts an enum value to its underlying integer type
template< typename EnumType >
typename std::underlying_type< EnumType >::type enumToInt( EnumType num )
{
	return static_cast< typename std::underlying_type< EnumType >::type >( num );
}


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_LANGUAGE_INCLUDED
