#include <cassert>

#define assert_msg( expr, message ) assert(( (void)message, expr ))

[[noreturn]] void critical_error( const char * format, ... );

#define SHOULDNT_HAPPEN( ... ) critical_error( __VA_ARGS__ )

#define TODO critical_error( "finish this!" );
