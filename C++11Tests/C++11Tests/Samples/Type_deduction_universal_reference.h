#include "stdafx.h"
#include <cstddef>

template<typename T>
void f(T&& param)
{
    //T is a reference
    //T is a universal reference
}

void myFunc1(const char param[])
{

}

template<typename T>
void myFunc3(T& param)
{

}

//reference of array
void myFunc4(const char(&param)[13])
{

}

// return size of an array as a compile-time constant. (The
// array parameter has no name, because we care only about
// the number of elements it contains.)
template<typename T, std::size_t N>                 // see info
constexpr std::size_t arraySize(T(&)[N]) noexcept  // below on
{                                                   // constexpr
    return N;                                         // and
}                                                   // noexcept

BEGIN_TEST(TestDeductionReference)
    {
        int x = 27;              // as before
        const int cx = x;        // as before
        const int& rx = x;       // as before

        f(x);                    // x is lvalue, so T is int&,
                                 // param's type is also int&

        f(cx);                   // cx is lvalue, so T is const int&,
                                 // param's type is also const int&

        f(rx);                   // rx is lvalue, so T is const int&,
                                 // param's type is also const int&

        f(27);                   // 27 is rvalue, so T is int,
                                 // param's type is therefore int&&

    }

    {
        const char name[] = "J. P. Briggs";  // name's type is
                                             // const char[13]
        myFunc1(name);
        myFunc3(name);
        myFunc4(name);
        const char * ptrToName = name;       // array decays to pointer
    }

    {
        const char name[] = "J. P. Briggs";  // name's type is
                                             // const char[13]
        std::size_t N = arraySize(name);

        int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };      // keyVals has
                                                         // 7 elements

        //because the "constexpr"
        int mappedVals[arraySize(keyVals)];              // so does
                                                         // mappedVals
    }
END_TEST()

