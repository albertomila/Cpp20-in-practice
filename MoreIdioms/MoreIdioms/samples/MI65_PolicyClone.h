#pragma once
#include "stdafx.h"

///////////////////////////////////////////////////////////////
template <class Apolicy>
class Host
{
    Apolicy direct_policy_use;

    // typedef int SomeInternalType;
    // Apolicy <SomeInternalType> InternalClone;  // Problem 1: Can't do this
};

///////////////////////////////////////////////////////////////
template 
<
	class T, 
	template <class T> 
	class Apolicy
>
class Host2
{
    Apolicy <T> common_use;  

    typedef int SomeInternalType;
    Apolicy <SomeInternalType> InternalClone;  
    // Can do this now but 
    // Problem 2: policies that require more than one type parameter can't participate.
};

///////////////////////////////////////////////////////////////
template <typename T>
class NiftyAlloc
{
public:
    template <typename Other>
    struct rebind // The Policy Clone idiom
    { 
        typedef NiftyAlloc <Other> other;
    };
    //...
};

///////////////////////////////////////////////////////////////
template <typename T, class Alloc = NiftyAlloc <T> >
class Vector 
{
public:
    typedef typename Alloc::template rebind<long>::other ClonePolicy;

    // Here, Alloc may not be a template class or a parametrized instantiation of
    // a class that takes unknown number of type parameters.
};

BEGIN_TEST(PolicyClone)
    Vector<int> v;

END_TEST()