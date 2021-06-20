//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: string-oriented utils
//======================================================================================================================

#ifndef CPPUTILS_STRING_INCLUDED
#define CPPUTILS_STRING_INCLUDED


#include "Essential.hpp"

#include <string>
#include <sstream>
#include <stdexcept>
#include <typeinfo>


namespace own {


//----------------------------------------------------------------------------------------------------------------------

// suffix s is C++14
inline std::string operator "" _s( const char * str, size_t size )
{
    return std::string( str, size );
}


//----------------------------------------------------------------------------------------------------------------------
//  parsing

template< typename DestType >
bool from_string( const std::string & src, DestType & dest )
{
	std::istringstream is( src );
	is >> dest;
	return !is.fail();
}

template< typename DestType >
DestType from_string( const std::string & src )
{
	DestType dest;
	if (!from_string( src, dest ))
	{
		throw std::invalid_argument( "\""+src+"\" is not a valid "+typeid( DestType ).name() );
	}
	return dest;
}


//----------------------------------------------------------------------------------------------------------------------
//  other

std::string to_lower( const std::string & str );

void to_lower_in_place( std::string & str );

bool starts_with( const std::string & str, const std::string & prefix );


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_STRING_INCLUDED
