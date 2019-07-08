#pragma once
#include "stdafx.h"
#include <typeinfo>

const // It is a const object...
class CNullPtr 
{
public:
    template<class T>
    inline operator T*() const // convertible to any type of null non-member pointer...
    { 
        const char* name = typeid( T ).name();
        return 0; 
    }

    template<class NullPtr_Data, class T>
    inline operator T NullPtr_Data::*() const   // or any type of null member pointer...
    { 
        return 0; 
    }

private:
    void operator&() const;  // Can't take address of NULL_PTR

};

CNullPtr NULL_PTR = {};

struct NullPtr_Data
{
    void func();
};

template<typename T> 
void g( T* t ) {}

template<typename T> 
void NullPtr_Foo1( T t ) {}

void NullPtr_Foo2(double *) {}
void NullPtr_Foo2(int) {}


BEGIN_TEST(NullPtr)
    char * ch = NULL_PTR;        // ok
	NullPtr_Foo2(NULL_PTR);             // Calls func(double *)
	NullPtr_Foo2(0);                   // Calls func(int)
    void (NullPtr_Data::*pmf2)() = 0;      // ok
    void (NullPtr_Data::*pmf)() = NULL_PTR; // ok
    CNullPtr n1, n2;
    n1 = n2;
    //CNullPtr *null = &n1;    // Address can't be taken.
    if (NULL_PTR == ch) {}       // ok
    if (NULL_PTR == pmf) {}      // Valid statement; but fails on g++ 4.1.1-4.5 due to bug #33990
    // for GCC 4: if ((typeof(pmf))NULL_PTR == pmf) {}
    const int n = 0;
    //if (NULL_PTR == n) {}        // Should not compile; but only Comeau shows an error.
    //int p = 0;
    //if (NULL_PTR == p) {}      // not ok
    //g (NULL_PTR);              // Can't deduce T
    int expr = 0;
    char* ch3 = expr ? NULL_PTR : NULL_PTR; // ch3 is the null pointer value
    //char* ch4 = expr ? 0 : NULL_PTR;     // error, types are not compatible
    //int n3 = expr ? NULL_PTR : NULL_PTR;  // error, NULL_PTR can’t be converted to int
    //int n4 = expr ? 0 : NULL_PTR;        // error, types are not compatible

	NullPtr_Foo1( 0 );                // deduces T = int
	NullPtr_Foo1( NULL_PTR );          // deduces T = CNullPtr
	NullPtr_Foo1( (float*) NULL_PTR ); // deduces T = float*

    sizeof( NULL_PTR );     // ok
    typeid( NULL_PTR );     // ok
    throw NULL_PTR;         // ok
END_TEST()