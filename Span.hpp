//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: own span substituting span from C++20
//======================================================================================================================

#ifndef CPPUTILS_SPAN_INCLUDED
#define CPPUTILS_SPAN_INCLUDED


#include <cstdint>
#include <type_traits>


namespace own {


//======================================================================================================================
/// Generalization over continuous-memory containers.
/** To be used instead of raw buffer pointers as often as possible. */

template< typename ElemType >
class span
{
	ElemType * _begin;
	ElemType * _end;

	using thisSpan = span< ElemType >;

 public:

	span() : _begin( nullptr ), _end( nullptr ) {}

	// the templates for other type are required to allow constructing  span< const char > from span< char >

	// construct manually from pair of pointers
	template< typename OtherType,
		typename std::enable_if<std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType * begin, ElemType * end ) : _begin( begin ), _end( end ) {}

	// construct manually from a data pointer and size
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType * data, size_t size ) : _begin( data ), _end( data + size ) {}

	// deduce from static C array
	template< typename OtherType, size_t Size,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType (& arr) [Size] ) : thisSpan( arr, Size ) {}

	// copy
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( const span< OtherType > & other ) : thisSpan( other.begin(), other.end() ) {}

	// assign
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span< ElemType > & operator=( const span< OtherType > & other )
		{ _begin = other.begin(); _end = other.end(); return *this; }

	ElemType * begin() const { return _begin; }
	ElemType * end() const { return _end; }
	ElemType * data() const { return _begin; }
	size_t size() const { return size_t( _end - _begin ); }
	bool empty() const { return _begin == _end; }

	template< typename OtherType >
	span< OtherType > cast() const
	{
		return { reinterpret_cast< OtherType * >( _begin ), reinterpret_cast< OtherType * >( _end ) };
	}
};


//======================================================================================================================
/// TODO
/** TODO */

template< typename ElemType, size_t Size >
class fixed_span
{
	ElemType * _begin;

 public:

	fixed_span() : _begin( nullptr ) {}

	// construct manually from a data pointer and template size
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span( OtherType * data ) : _begin( data ) {}

	// copy
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span( const fixed_span< OtherType, Size > & other ) : _begin( other.begin() ) {}

	// assign
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span< ElemType, Size > & operator=( fixed_span< OtherType, Size > other )
		{ _begin = other.begin(); return *this; }

	ElemType * begin() const { return _begin; }
	ElemType * end() const { return _begin + Size; }
	ElemType * data() const { return _begin; }
	size_t size() const { return Size; }
	bool empty() const { return Size == 0; }

	template< typename OtherType >
	fixed_span< OtherType, Size > cast() const
	{
		return { reinterpret_cast< OtherType * >( _begin ) };
	}
};


//======================================================================================================================
//  specialized spans

class byte_span : public span< uint8_t >
{
	using baseSpan = span< uint8_t >;

 public:

	using baseSpan::span;

	byte_span( const baseSpan & other ) : baseSpan( other ) {}
	byte_span & operator=( const baseSpan & other ) { baseSpan::operator=( other ); return *this; }

	// allow using chars where bytes are expected
	byte_span( const span< char > & other )
		: baseSpan( reinterpret_cast< uint8_t * >( other.data() ), other.size() ) {}
	template< size_t Size >
	byte_span( char (& arr) [Size] )
		: baseSpan( reinterpret_cast< uint8_t * >( arr ), Size ) {}
};

class const_byte_span : public span< const uint8_t >
{
	using baseSpan = span< const uint8_t >;

 public:

	using baseSpan::span;

	const_byte_span( const baseSpan & other ) : baseSpan( other ) {}
	const_byte_span & operator=( const baseSpan & other ) { baseSpan::operator=( other ); return *this; }

	// allow using chars where bytes are expected
	// TODO: simpler
	const_byte_span( const span< const char > & other )
		: baseSpan( reinterpret_cast< const uint8_t * >( other.data() ), other.size() ) {}
	const_byte_span( const span< char > & other )
		: baseSpan( reinterpret_cast< uint8_t * >( other.data() ), other.size() ) {}
	template< size_t Size >
	const_byte_span( const char (& arr) [Size] )
		: baseSpan( reinterpret_cast< const uint8_t * >( arr ), Size ) {}
	template< size_t Size >
	const_byte_span( char (& arr) [Size] )
		: baseSpan( reinterpret_cast< uint8_t * >( arr ), Size ) {}
};

class char_span : public span< char >
{
	using baseSpan = span< char >;

 public:

	using baseSpan::span;

	char_span( const baseSpan & other ) : baseSpan( other ) {}
	char_span & operator=( const baseSpan & other ) { baseSpan::operator=( other ); return *this; }

	// allow using bytes where chars are expected
	char_span( const span< uint8_t > & other )
		: baseSpan( reinterpret_cast< char * >( other.data() ), other.size() ) {}
	template< size_t Size >
	char_span( const uint8_t (& arr) [Size] )
		: baseSpan( reinterpret_cast< char * >( arr ), Size ) {}
};

class const_char_span : public span< const char >
{
	using baseSpan = span< const char >;

 public:

	using baseSpan::span;

	const_char_span( const baseSpan & other ) : baseSpan( other ) {}
	const_char_span & operator=( const baseSpan & other ) { baseSpan::operator=( other ); return *this; }

	// allow using bytes where chars are expected
	// TODO: simpler
	const_char_span( const span< const uint8_t > & other )
		: baseSpan( reinterpret_cast< const char * >( other.data() ), other.size() ) {}
	const_char_span( const span< uint8_t > & other )
		: baseSpan( reinterpret_cast< char * >( other.data() ), other.size() ) {}
	template< size_t Size >
	const_char_span( const uint8_t (& arr) [Size] )
		: baseSpan( reinterpret_cast< const char * >( arr ), Size ) {}
	template< size_t Size >
	const_char_span( uint8_t (& arr) [Size] )
		: baseSpan( reinterpret_cast< char * >( arr ), Size ) {}
};

template< size_t Size >
using fixed_byte_span = fixed_span< uint8_t, Size >;

template< size_t Size >
using fixed_const_byte_span = fixed_span< const uint8_t, Size >;

template< size_t Size >
using fixed_char_span = fixed_span< char, Size >;

template< size_t Size >
using fixed_char_byte_span = fixed_span< const char, Size >;


//======================================================================================================================


} // namespace own


#endif // CPPUTILS_SPAN_INCLUDED
