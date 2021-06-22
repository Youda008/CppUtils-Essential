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

template< typename ElemType, size_t Size >
auto make_fixex_span( std::array< ElemType, Size > & arr )
 -> fixed_span< typename std::remove_reference< decltype( arr[0] ) >::type, Size >
{
	return { arr };
}
template< typename ElemType, size_t Size >
auto make_fixex_span( const std::array< ElemType, Size > & arr )
 -> fixed_span< const typename std::remove_reference< decltype( arr[0] ) >::type, Size >
{
	return { arr };
}


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_CONTAINER_INCLUDED
