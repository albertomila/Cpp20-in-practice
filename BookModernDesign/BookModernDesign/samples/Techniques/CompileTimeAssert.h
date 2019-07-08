#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

//#define STATIC_CHECK(expr) { char unnamed[(expr) ? 1 : 0]; }

template<bool> 
struct CompileTimeError;

template<> 
struct CompileTimeError<true> 
{
};
/*
#define STATIC_CHECK(expr) \
    (CompileTimeError<(expr) != 0>())
    */
template<bool> 
struct CompileTimeChecker
{
    CompileTimeChecker(...);
};
template<> 
struct CompileTimeChecker<false> 
{
};

#define STATIC_CHECK(expr, msg) \
{\
class ERROR_##msg {}; \
    (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg())));\
}





template <class To, class From>
To safe_reinterpret_cast(From from)
{
    STATIC_CHECK(sizeof(From) <= sizeof(To),
        Destination_Type_Too_Narrow);
    return reinterpret_cast<To>(from);
}


BEGIN_TEST(CompileTimeAssert)
    string* somePointer = new string("Test");
    string* c = safe_reinterpret_cast<string*>(somePointer);
END_TEST()