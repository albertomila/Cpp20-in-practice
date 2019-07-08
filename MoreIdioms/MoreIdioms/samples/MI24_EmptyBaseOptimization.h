#pragma once
#include "stdafx.h"
///////////////////////////////////////////
class EmptyClass {};
class EmptyClass2 {};

///////////////////////////////////////////
class AnInt  : public EmptyClass 
{
    int data;
};   // size = sizeof(int)

class AnotherEmpty : public EmptyClass {};  // size =  1

///////////////////////////////////////////
class E1 {};
class E2 {};

// **** before EBCO ****

class Foo1
{
    E1 e1;
    E2 e2;
    int data;
}; // sizeof(Foo1) = 8

// **** after EBCO ****

class Foo2 : private E1, private E2 
{
    int data;
}; // sizeof(Foo2) = 4


///////////////////////////////////////////
template <class Base1, class Base2, class Member>
struct BaseOptimization : Base1, Base2 
{
    BaseOptimization() 
    {
    }

    BaseOptimization(Base1 const& b1, Base2 const & b2, Member const& mem)
        : Base1(b1), Base2(b2), m(mem) 
    {
    }

    Base1 * first()  
    { 
        return this; 
    }

    Base2 * second() 
    { 
        return this; 
    }

    Member member;
};

class Foo3
{
    BaseOptimization<E1, E2, int> data;
}; // sizeof(Foo3) = 4


BEGIN_TEST(EmptyBaseOptimization)
    size_t size1 = sizeof( int );

    size_t size2 = sizeof( EmptyClass );
    size_t size3 = sizeof( AnInt );
    size_t size4 = sizeof( AnotherEmpty );

    size_t size5 = sizeof( Foo1 );
    size_t size6 = sizeof( Foo2 );
    size_t size7 = sizeof( Foo3 );
END_TEST()