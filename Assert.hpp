#include <cassert>
#include <stdexcept>

#ifdef CRITICALS_CATCHABLE
	#define assert_msg( expr, message ) if (!(expr)) throw std::logic_error( message )
#else
	#define assert_msg( expr, message ) assert(( (void)message, expr ))
#endif
