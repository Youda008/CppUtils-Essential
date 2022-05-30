//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: custom type traits helpers
//======================================================================================================================

#ifndef CPPUTILS_TYPETRAITS_INCLUDED
#define CPPUTILS_TYPETRAITS_INCLUDED


#include "Essential.hpp"

#include <type_traits>
#include <array>    // data, size, begin, end


/// a syntax simplification for constraining template types
#define REQUIRES( ... ) typename std::enable_if< __VA_ARGS__, int >::type = 0


namespace fut {


template< typename T >
struct remove_cvref
{
    using type = typename std::remove_cv< typename std::remove_reference<T>::type >::type;
};


} // namespace fut


namespace own {


/// This determines types that are convertible to integer and serializable to big endian.
template< typename T >
struct is_int_or_enum
{
	static constexpr bool value = std::is_integral<T>::value || std::is_enum<T>::value;
};

/// For integer it returns the integer, and for enum it returns its underlying_type.
// https://stackoverflow.com/questions/56972288/metaprogramming-construct-that-returns-underlying-type-for-an-enum-and-integer-f
template< typename T >
struct int_type
{
	using type = typename std::conditional<
		/*if*/ std::is_enum<T>::value,
		/*then*/ std::underlying_type<T>,
		/*else*/ std::enable_if< std::is_integral<T>::value, T >
	>::type::type;
};

template< typename T1, typename T2 >
struct bigger_type
{
	using type = typename std::conditional<
		/*if*/ (sizeof(T1) >= sizeof(T2)),
		/*then*/ T1,
		/*else*/ T2
	>::type;
};

template< typename SrcT, typename DstT >
struct corresponding_constness
{
	using type = typename std::conditional<
		/*if*/ std::is_const< SrcT >::value,
		/*then*/ std::add_const< DstT >,
		/*else*/ std::remove_const< DstT >
	>::type::type;
};

template< typename T >
struct range_element
{
	using type = typename std::remove_reference< decltype( *std::begin( std::declval< T & >() ) ) >::type;
};

template< typename T >
struct range_value
{
	using type = typename fut::remove_cvref< decltype( *std::begin( std::declval< T & >() ) ) >::type;
};

template< typename T >
struct is_byte_range
{
	static constexpr bool value = std::is_same< typename range_value<T>::type, uint8_t >::value;
};


template< typename T >
struct is_c_array : std::false_type {};
template< typename T, size_t N >
struct is_c_array< T [N] > : std::true_type {};
template< typename T, size_t N >
struct is_c_array< T (&)[N] > : std::true_type {};

template< typename T, typename ElemType >
struct is_c_array_of
{
	static constexpr bool value = is_c_array<T>::value && std::is_same< typename range_value<T>::type, ElemType >::value;
};

namespace impl
{
	template< typename T >
	struct is_std_array : std::false_type {};
	template< typename ElemType, size_t size_ >
	struct is_std_array< std::array< ElemType, size_ > > : std::true_type {};
}
template< typename T >
struct is_std_array : impl::is_std_array< typename std::remove_cv<T>::type > {};


} // namespace own


#endif // CPPUTILS_TYPETRAITS_INCLUDED
