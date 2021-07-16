//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: own span substituting span from C++20
//======================================================================================================================

#ifndef CPPUTILS_SPAN_INCLUDED
#define CPPUTILS_SPAN_INCLUDED


#include <cstddef>  // size_t
#include <cstdint>  // uint8_t
#include <type_traits>


namespace own {


//======================================================================================================================
/// Variant of span with compile-time length.
/** Use this when you know already know how long the span will be when writing your code. */

template< typename ElemType, size_t Size >
class fixed_span
{
	ElemType * _begin;

 public:

	fixed_span() noexcept : _begin( nullptr ) {}

	// construct manually from a data pointer and template size
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span( OtherType * data ) noexcept : _begin( data ) {}

	// copy
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span( const fixed_span< OtherType, Size > & other ) noexcept : _begin( other.begin() ) {}

	// assign
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	fixed_span< ElemType, Size > & operator=( fixed_span< OtherType, Size > other ) noexcept
		{ _begin = other.begin(); return *this; }

	ElemType * begin() const noexcept { return _begin; }
	ElemType * end() const noexcept { return _begin + Size; }
	ElemType * data() const noexcept { return _begin; }
	size_t size() const noexcept { return Size; }
	bool empty() const noexcept { return Size == 0; }

	template< typename OtherType >
	fixed_span< OtherType, Size > cast() const noexcept
	{
		return { reinterpret_cast< OtherType * >( _begin ) };
	}
};


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

	span() noexcept : _begin( nullptr ), _end( nullptr ) {}

	// the templates with OtherType are required to allow constructing  span< const char > from span< char >

	// construct manually from pair of pointers
	template< typename OtherType,
		typename std::enable_if<std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType * begin, ElemType * end ) noexcept : _begin( begin ), _end( end ) {}

	// construct manually from a data pointer and size
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType * data, size_t size ) noexcept : _begin( data ), _end( data + size ) {}

	// construct from fixed_span
	template< typename OtherType, size_t Size,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( const fixed_span< OtherType, Size > & other ) noexcept : thisSpan( other.data, Size ) {}

	// deduce from static C array
	template< typename OtherType, size_t Size,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( OtherType (& arr) [Size] ) noexcept : thisSpan( arr, Size ) {}

	// copy
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span( const span< OtherType > & other ) noexcept : thisSpan( other.begin(), other.end() ) {}

	// assign
	template< typename OtherType,
		typename std::enable_if< std::is_convertible< OtherType*, ElemType* >::value, int >::type = 0 >
	span< ElemType > & operator=( const span< OtherType > & other ) noexcept
		{ _begin = other.begin(); _end = other.end(); return *this; }

	ElemType * begin() const noexcept { return _begin; }
	ElemType * end() const noexcept { return _end; }
	ElemType * data() const noexcept { return _begin; }
	size_t size() const noexcept { return size_t( _end - _begin ); }
	bool empty() const noexcept { return _begin == _end; }

	template< typename OtherType >
	span< OtherType > cast() const noexcept
	{
		return { reinterpret_cast< OtherType * >( _begin ), reinterpret_cast< OtherType * >( _end ) };
	}
};



//======================================================================================================================
//  specialized spans

class byte_span : public span< uint8_t >
{
	using baseSpan = span< uint8_t >;

 public:

	using span< uint8_t >::span;

	byte_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	byte_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	span< char > toChars() const noexcept { return { reinterpret_cast< char * >( data() ), size() }; }
};

class const_byte_span : public span< const uint8_t >
{
	using baseSpan = span< const uint8_t >;

 public:

	using span< const uint8_t >::span;

	const_byte_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	const_byte_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	span< const char > toChars() const noexcept { return { reinterpret_cast< const char * >( data() ), size() }; }
};

class char_span : public span< char >
{
	using baseSpan = span< char >;

 public:

	using span< char >::span;

	char_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	char_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	span< uint8_t > toBytes() const noexcept { return { reinterpret_cast< uint8_t * >( data() ), size() }; }
};

class const_char_span : public span< const char >
{
	using baseSpan = span< const char >;

 public:

	using span< const char >::span;

	const_char_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	const_char_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	span< const uint8_t > toBytes() const noexcept { return { reinterpret_cast< const uint8_t * >( data() ), size() }; }
};




template< size_t Size >
class fixed_byte_span : public fixed_span< uint8_t, Size >
{
	using baseSpan = fixed_span< uint8_t, Size >;

 public:

	using fixed_span< uint8_t, Size >::fixed_span;

	fixed_byte_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	fixed_byte_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	fixed_span< char, Size > toChars() const noexcept { return { reinterpret_cast< char * >( this->data() ) }; }
};

template< size_t Size >
class fixed_const_byte_span : public fixed_span< const uint8_t, Size >
{
	using baseSpan = fixed_span< const uint8_t, Size >;

 public:

	using fixed_span< const uint8_t, Size >::fixed_span;

	fixed_const_byte_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	fixed_const_byte_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	fixed_span< const char, Size > toChars() const noexcept { return { reinterpret_cast< const char * >( this->data() ) }; }
};

template< size_t Size >
class fixed_char_span : public fixed_span< char, Size >
{
	using baseSpan = fixed_span< char, Size >;

 public:

	using fixed_span< char, Size >::fixed_span;

	fixed_char_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	fixed_char_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	fixed_span< uint8_t, Size > toBytes() const noexcept { return { reinterpret_cast< uint8_t * >( this->data() ) }; }
};

template< size_t Size >
class fixed_const_char_span : public fixed_span< const char, Size >
{
	using baseSpan = fixed_span< const char, Size >;

 public:

	using fixed_span< const char, Size >::fixed_span;

	fixed_const_char_span( const baseSpan & other ) noexcept : baseSpan( other ) {}
	fixed_const_char_span & operator=( const baseSpan & other ) noexcept { baseSpan::operator=( other ); return *this; }

	fixed_span< const uint8_t, Size > toBytes() const noexcept { return { reinterpret_cast< const uint8_t * >( this->data() ) }; }
};


//======================================================================================================================
//  deduce template params from C arrays and C string literals

template< typename ElemType, size_t Size >
fixed_span< ElemType, Size > make_span( ElemType (& arr) [Size] ) noexcept
{
	return fixed_span< ElemType, Size >( arr );
}

template< size_t Size >
fixed_byte_span< Size > make_span( uint8_t (& arr) [Size] ) noexcept
{
	return fixed_byte_span< Size >( arr );
}

template< size_t Size >
fixed_char_span< Size > make_span( char (& arr) [Size] ) noexcept
{
	return fixed_char_span< Size >( arr );
}


//======================================================================================================================


} // namespace own


#endif // CPPUTILS_SPAN_INCLUDED
