//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Created on:  17.06.2021
// Description: string-oriented utils
//======================================================================================================================

#include "StringUtils.hpp"

#include <cctype>


namespace own {


// TODO: more efficient version using stream buffers
// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/libstdc%2B%2B-v3/include/ext/vstring.tcc
void read_until( std::istream & is, std::string & dest, char delim )
{
	while (true)
	{
		char c = char( is.get() );
		if (!is.good() || c == delim)
			break;
		dest += c;
	}
}

std::string read_until( std::istream & is, char delim )
{
	std::ostringstream os;
	while (true)
	{
		char c = char( is.get() );
		if (!is.good() || c == delim)
			break;
		os << c;
	}
	return os.str();
}

void to_lower_in_place( std::string & str )
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		str[i] = char( tolower( str[i] ) );
	}
}

std::string to_lower( const std::string & str )
{
	std::string copy( str );
	to_lower_in_place( copy );
	return copy;
}

bool starts_with( const std::string & str, const std::string & prefix )
{
	return str.compare( 0, prefix.size(), prefix ) == 0;
}


} // namespace own
