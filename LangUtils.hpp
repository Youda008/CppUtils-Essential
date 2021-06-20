//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: template helpers, container helpers and backports from newer C++ standards
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
constexpr std::reverse_iterator<Iter> make_reverse_iterator( Iter i )
{
    return std::reverse_iterator<Iter>(i);
}


//----------------------------------------------------------------------------------------------------------------------
//  container helpers

template< typename Iterator, typename Distance >
Iterator advance( Iterator it, Distance n )
{
	std::advance( it, n );
	return it;
}

template< typename Container >
auto make_span( Container & cont ) -> span< typename std::remove_reference< decltype( *cont.data() ) >::type >
{
	return { cont.data(), cont.data() + cont.size() };
}
template< typename Container >
auto make_span( const Container & cont ) -> span< typename std::remove_reference< decltype( *cont.data() ) >::type >
{
	return { cont.data(), cont.data() + cont.size() };
}
template< typename ElemType, size_t size >
auto make_span( ElemType (& arr) [size] ) -> span< ElemType >
{
	return { &*std::begin(arr), &*std::end(arr) };
}
template< typename ElemType, size_t size >
auto make_span( const ElemType (& arr) [size] ) -> span< const ElemType >
{
	return { &*std::begin(arr), &*std::end(arr) };
}
template< size_t size >
auto make_span( const char (& arr) [size] ) -> span< const char >
{
	return { reinterpret_cast< const char * >( arr ), reinterpret_cast< const char * >( arr ) + size };
}


//----------------------------------------------------------------------------------------------------------------------
//  scope guards

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
//  type traits helpers

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
