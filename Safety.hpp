//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: declarations and utils for memory safety
//======================================================================================================================

#ifndef CPPUTILS_SAFETY_INCLUDED
#define CPPUTILS_SAFETY_INCLUDED


enum class SafetyChecks
{
	Disabled,
	Enabled
};

#ifdef DEBUG
	constexpr SafetyChecks defaultSafetyChecks = SafetyChecks::Enabled;
#else
	constexpr SafetyChecks defaultSafetyChecks = SafetyChecks::Disabled;
#endif // DEBUG


#endif // CPPUTILS_SAFETY_INCLUDED
