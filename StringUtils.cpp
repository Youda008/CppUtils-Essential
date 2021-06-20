//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: string-oriented utils
//======================================================================================================================

#include "StringUtils.hpp"

#include <cctype>  // isspace, tolower


namespace own {


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
