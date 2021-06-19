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

#include <iterator>
#include <type_traits>


namespace own {


//----------------------------------------------------------------------------------------------------------------------
//  container helpers

// std::size is C++17, and since we want to support C++11 we have to make our own
template< typename Container >
constexpr size_t size( const Container & cont )
{
	return std::end(cont) - std::begin(cont);
}

template< typename Iterator, typename Distance >
Iterator advance( Iterator it, Distance n )
{
	std::advance( it, n );
	return it;
}


//----------------------------------------------------------------------------------------------------------------------
//  span - a generalization over continuous-memory containers

template< typename ElemType >
class span
{
	ElemType * _begin;
	ElemType * _end;

 public:

	span() : _begin( nullptr ), _end( nullptr ) {}
	template< typename OtherType >
	span( OtherType * begin, OtherType * end ) : _begin( begin ), _end( end ) {}
	template< typename OtherType >
	span( OtherType * data, size_t size ) : _begin( data ), _end( data + size ) {}
	template< typename OtherType >
	span( span< OtherType > other ) : _begin( other.begin() ), _end( other.end() ) {}

	template< typename OtherType >
	span< ElemType > & operator=( span< OtherType > other ) { _begin = other.begin(); _end = other.end(); return *this; }

	ElemType * begin() const { return _begin; }
	ElemType * end() const { return _end; }
	ElemType * data() const { return _begin; }
	size_t size() const { return _end - _begin; }
	bool empty() const { return _begin == _end; }

	template< typename OtherType >
	span< OtherType > cast() const
	{
		return { reinterpret_cast< OtherType * >( _begin ), reinterpret_cast< OtherType * >( _end ) };
	}
};

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
//  compiler-dependent

/// Compiler dependent way to silence unused variable warnings in C++11.
/** This library is limited to C++11, so the standardized [[maybe_unused]] is not usable. This will silence the warnings
  * in gcc and clang. Users of other compilers will have to deal with occasional warnings or disable them completely
  * with command line argument. */
#define MAYBE_UNUSED

#undef MAYBE_UNUSED
#ifdef __GNUC__
	#define MAYBE_UNUSED __attribute__((unused))
#else
	#define MAYBE_UNUSED
#endif


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_LANGUAGE_INCLUDED
