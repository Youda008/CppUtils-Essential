//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: helpers that require declarations of STL containers
//======================================================================================================================

#ifndef CPPUTILS_CONTAINERS_INCLUDED
#define CPPUTILS_CONTAINERS_INCLUDED


#include "Essential.hpp"

#include "Span.hpp"

#include <iterator>  // advance, begin, end
#include <array>
#include <vector>


namespace own {


//----------------------------------------------------------------------------------------------------------------------
//  own::span helpers

template< typename ElemType >
auto make_span( std::vector< ElemType > & cont ) noexcept
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}
template< typename ElemType >
auto make_span( const std::vector< ElemType > & cont ) noexcept
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}

template< typename ElemType, size_t Size >
auto make_span( std::array< ElemType, Size > & cont ) noexcept
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}
template< typename ElemType, size_t Size >
auto make_span( const std::array< ElemType, Size > & cont ) noexcept
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}

template< typename ElemType, size_t Size >
auto make_fixex_span( std::array< ElemType, Size > & cont ) noexcept
 -> fixed_span< typename std::remove_reference< decltype( cont[0] ) >::type, Size >
{
	return { cont.data() };
}
template< typename ElemType, size_t Size >
auto make_fixex_span( const std::array< ElemType, Size > & cont ) noexcept
 -> fixed_span< const typename std::remove_reference< decltype( cont[0] ) >::type, Size >
{
	return { cont.data() };
}


//----------------------------------------------------------------------------------------------------------------------
//  misc

template< typename Type, typename std::enable_if< std::is_trivial<Type>::value, int >::type = 0 >
size_t sizeofVector( const std::vector< Type > & vec ) noexcept
{
	return vec.size() * sizeof( Type );
}

template< typename Type, size_t Size, typename std::enable_if< std::is_trivial<Type>::value, int >::type = 0 >
size_t sizeofArray( const std::array< Type, Size > & arr ) noexcept
{
	return arr.size() * sizeof( Type );
}


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_CONTAINER_INCLUDED
