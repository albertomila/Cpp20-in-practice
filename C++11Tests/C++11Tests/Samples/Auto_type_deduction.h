// C++11Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <initializer_list>


void someFunc(int, double)    // someFunc is a function;
{
    // type is void(int, double)
}

template<typename T>
void InitializerListT(std::initializer_list<T> initList)
{

}

auto ShouldBeDeduced()
{
    return "hello";
}

BEGIN_TEST(TestAutoTypeDeduction)
    auto x = 27;          // case 3 (x is neither ptr nor reference)
    
    const auto cx = x;    // case 3 (cx isn't either)
    
    const auto& rx = x;   // case 1 (rx is a non-universal ref.)

    auto&& uref1 = x;     // x is int and lvalue,
                          // so uref1's type is int&

    auto&& uref2 = cx;    // cx is const int and lvalue,
                          // so uref2's type is const int&

    auto&& uref3 = 27;    // 27 is int and rvalue,
                          // so uref3's type is int&&

    const char name[] =            // name's type is const char[13]
        "R. N. Briggs";

    auto arr1 = name;              // arr1's type is const char*

    auto& arr2 = name;             // arr2's type is
                                   // const char (&)[13]


    auto func1 = someFunc;         // func1's type is
                                   // void (*)(int, double)

    auto& func2 = someFunc;        // func2's type is
                                   // void (&)(int, double)

    auto x3 = { 27 };         // type is std::initializer_list<int>,
                              // value is { 27 }

    auto x4{ 27 };            // ditto

    InitializerListT( { 11, 23, 9 } );

    auto f1 = ShouldBeDeduced();
END_TEST()
