//======================================================================================================================
// Project: CppUtils
//----------------------------------------------------------------------------------------------------------------------
// Author:      Jan Broz (Youda008)
// Description: own span substituting span from C++20
//======================================================================================================================

#ifndef CPPUTILS_SPAN_INCLUDED
#define CPPUTILS_SPAN_INCLUDED


#include <stddef.h>  // size_t


namespace own {


/// Generalization over continuous-memory containers.
/** To be used instead of raw buffer pointers as often as possible. */
template< typename ElemType >
class span
{
	ElemType * _begin;
	ElemType * _end;

 public:

	span() : _begin( nullptr ), _end( nullptr ) {}

	// construct manually from pair of pointers or data and size
	span( ElemType * begin, ElemType * end ) : _begin( begin ), _end( end ) {}
	span( ElemType * data, size_t size ) : _begin( data ), _end( data + size ) {}

	// deduce from container
	template< typename Container >
	span( Container & cont ) : _begin( cont.data() ), _end( cont.data() + cont.size() ){}
	template< typename Container >
	span( const Container & cont ) : _begin( cont.data() ), _end( cont.data() + cont.size() ) {}

	// deduce from static C array
	template< size_t size >
	span( ElemType (& arr) [size] ) : _begin( arr ), _end( arr + size ) {}
	//template< size_t size >
	//span( const ElemType (& arr) [size] ) : _begin( arr ), _end( arr + size ) {}

	span( const span< ElemType > & other ) : _begin( other.begin() ), _end( other.end() ) {}

	span< ElemType > & operator=( span< ElemType > other ) { _begin = other.begin(); _end = other.end(); return *this; }

	ElemType * begin() const { return _begin; }
	ElemType * end() const { return _end; }
	ElemType * data() const { return _begin; }
	size_t size() const { return _end - _begin; }
	bool empty() const { return _begin == _end; }

	template< typename OtherType >
	span< OtherType > cast() const
	{
		return { reinterpret_cast< OtherType * >( _begin ), reinterpret_cast< OtherType * >( _end ) };
	}
};


// TODO: fixed span


} // namespace own


#endif // CPPUTILS_SPAN_INCLUDED
