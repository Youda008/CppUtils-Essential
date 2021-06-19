//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Created on:  17.06.2021
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

template< typename DestType >
DestType read( std::istream & is )
{
	DestType dest;
	is >> dest;
	if (!is.good())
	{
		throw std::invalid_argument( "input does not contain valid "_s + typeid( DestType ).name() );
	}
	return dest;
}

void read_until( std::istream & is, std::string & dest, char delim );
std::string read_until( std::istream & is, char delim );


//----------------------------------------------------------------------------------------------------------------------
//  stream utils

class repeat_char
{
 public:
	repeat_char( char c, size_t count ) : c(c), count(count) {}
	friend std::ostream & operator<<( std::ostream & os, repeat_char repeat )
	{
		while (repeat.count --> 0)
			os << repeat.c;
		return os;
	}
 private:
	char c;
	size_t count;
};


//----------------------------------------------------------------------------------------------------------------------
//  other

std::string to_lower( const std::string & str );

void to_lower_in_place( std::string & str );

bool starts_with( const std::string & str, const std::string & prefix );


//----------------------------------------------------------------------------------------------------------------------


} // namespace own


#endif // CPPUTILS_STRING_INCLUDED
