#pragma once
#include "stdafx.h"

/////////////////////////////////////////////////////
/*
//Motivation

class B {};
class D : public B {};
template <class T>
class Helper {};

B *bptr;
D *dptr;
bptr = dptr; // OK; permitted by C++

Helper<B> hb;
Helper<D> hd; 
hb = hd; // Not allowed but could be very useful
*/
#include <iostream>
class B 
{
};

class D : public B 
{
};

template <class T>
class Ptr
{
public:
    Ptr () 
    {
    }

    Ptr (Ptr const & p)
        : m_ptr (p.m_ptr)
    {
        std::cout << "Copy constructor\n";
    }

    // Supporting coercion using member template constructor.
    // This is not a copy constructor, but behaves similarly.
    template <class U>
    Ptr ( const Ptr <U>& p )
        : m_ptr (const_cast<U*>( p.GetValue() )) // Implicit conversion from U to T required
    {
        std::cout << "Coercing member template constructor\n";
    }

    // Copy assignment operator.
    Ptr & operator = (Ptr const & p)
    {
        m_ptr = p.m_ptr;
        std::cout << "Copy assignment operator\n";
        return *this;
    }

    // Supporting coercion using member template assignment operator.
    // This is not the copy assignment operator, but works similarly.
    template <class U>
    Ptr & operator = ( const Ptr <U>& p )
    {
        m_ptr = const_cast<U*>( p.GetValue() ); // Implicit conversion from U to T required
        std::cout << "Coercing member template assignment operator\n";
        return *this;
    } 

    const T* GetValue() const{ return m_ptr; }

private:
    T* m_ptr;
};


BEGIN_TEST(CohercionMemberTemplate)
    Ptr <D> d_ptr;
    Ptr <B> b_ptr (d_ptr); // Now supported
    b_ptr = d_ptr;         // Now supported

	END_TEST()