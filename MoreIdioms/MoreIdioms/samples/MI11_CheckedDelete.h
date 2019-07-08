#pragma once
#include "stdafx.h"
#include <xstddef>

////////////////////////////////////////////////////////////////////////////
template<class T> 
inline void checked_delete(T * x)
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
   // (void) sizeof(type_must_be_complete);
	int size_of = sizeof(type_must_be_complete);
    delete x;
}

////////////////////////////////////////////////////////////////////////////
template<class T> 
struct checked_deleter : std::unary_function <T *, void>
{
    void operator()(T * x) const
    {
        checked_delete(x);
    }
};

//type incomplete, compilation error.
//struct Object;


//ok
struct Object
{
	int* x = NULL;

	Object()
	{
		x = new int[128];
	}

	// this user-defined destructor won't be called when delete
	// is called on a partially-defined (i.e., predeclared) Object
    ~Object() 
	{ 
		delete[] x;
    }
};



BEGIN_TEST(CheckDelete)
    Object* oNull = NULL;
	Object* o = new Object();
    checked_delete<Object>( oNull );
	checked_delete<Object>(o);
END_TEST()