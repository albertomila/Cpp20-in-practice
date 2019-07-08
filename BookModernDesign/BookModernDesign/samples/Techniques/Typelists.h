#pragma once
#include "stdafx.h"

class NullType {};
struct EmptyType {};

template <class T, class U>
struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

#define TYPELIST_1(T1)                      \
        Typelist<T1, NullType> 
            
#define TYPELIST_2(T1, T2)                  \
        Typelist<T1, TYPELIST_1(T2) > 

#define TYPELIST_3(T1, T2, T3)              \
        Typelist<T1, TYPELIST_2(T2, T3) > 

#define TYPELIST_4(T1, T2, T3, T4)          \
        Typelist<T1, TYPELIST_3(T2, T3, T4) >

typedef 
    TYPELIST_4(   signed char
                , short int
                , int
                , long int)
SignedIntegrals;


template <class TList, unsigned int index,
typename DefaultType = NullType>
struct TypeAtNonStrict
{
    typedef DefaultType Result;
};
       
template <class Head, class Tail, typename DefaultType>
struct TypeAtNonStrict<Typelist<Head, Tail>, 0, DefaultType>
{
    typedef Head Result;
};
         
template <class Head, class Tail, unsigned int i, typename DefaultType>
struct TypeAtNonStrict<Typelist<Head, Tail>, i, DefaultType>
{
    typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
};