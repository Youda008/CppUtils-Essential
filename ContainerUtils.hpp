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
auto make_span( std::vector< ElemType > & cont )
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}
template< typename ElemType >
auto make_span( const std::vector< ElemType > & cont )
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}

template< typename ElemType, size_t Size >
auto make_span( std::array< ElemType, Size > & cont )
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}
template< typename ElemType, size_t Size >
auto make_span( const std::array< ElemType, Size > & cont )
 -> span< typename std::remove_reference< decltype( cont[0] ) >::type >
{
	return { cont.data(), cont.size() };
}

template< typename ElemType, size_t Size >
auto make_fixex_span( std::array< ElemType, Size > & cont )
 -> fixed_span< typename std::remove_reference< decltype( cont[0] ) >::type, Size >
{
	return { cont.data() };
}
template< typename ElemType, size_t Size >
auto make_fixex_span( const std::array< ElemType, Size > & cont )
 -> fixed_span< const typename std::remove_reference< decltype( cont[0] ) >::type, Size >
{
	return { cont.data() };
}


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_CONTAINER_INCLUDED
