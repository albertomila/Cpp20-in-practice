#pragma once
#include "stdafx.h"

class CNonaddressable 
{
    typedef double useless_type;
public:
    CNonaddressable( int x )
        : m_x( x )
    {
    }
    int m_x;
private:
    useless_type operator&() const;
};

//solution
template <class T>
T* AddressOf(T& v)
{
    
    const volatile char& value1 = reinterpret_cast<const volatile char &>(v);
    char& value2                = const_cast<char&>( value1 );
    char* value3                = &value2;
    T* value4                   = reinterpret_cast<T *>( value3 );
    return value4;
    

    /*
    char& value1    = reinterpret_cast<char &>(v);
    char* value3    = &value1;
    T* value4       = reinterpret_cast<T *>( value3 );
    return value4;
    */
    /*
    return reinterpret_cast<T *>
            (
                & const_cast<char&>
                (
                    reinterpret_cast<const volatile char &>(v)
                )
            );*/
}

BEGIN_TEST(Address)
    CNonaddressable na( 99 );
    CNonaddressable * naptr = AddressOf<CNonaddressable>(na); // No more compiler error.

    //problem
    //CNonaddressable * naptr = &na; // Compiler error here.

	END_TEST()