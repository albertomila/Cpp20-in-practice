#include "stdafx.h"
#include <vector>


//C++11
template<typename Container, typename Index> 
auto MethodTest11(Container& c, Index i) -> decltype(c[i])
{
    return c[i];
}

// final C++11 version
template<typename Container, typename Index>       
auto MethodTest11Final(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i])
{
    return std::forward<Container>(c)[i];
}

//C++14
template<typename Container, typename Index> 
decltype(auto) MethodTest14(Container& c, Index i)
{
    return c[i];
}

// final C++14 version
template<typename Container, typename Index>
decltype(auto) MethodTest14Final(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}

decltype(auto) decltypef1()
{
    int x = 0;
    return x;        // decltype(x) is int, so f1 returns int
}

decltype(auto) decltypef2()
{
    int x = 0;
    return (x);      // decltype((x)) is int&, so f2 returns int&
    //returning referece of a local variable! undefined behavior!
}

BEGIN_TEST(TestDeclType)
    const int i = 0;           // decltype(i) is const int
    decltype(i) z = 99;

    int x = 0;
    std::vector<int> v;         // decltype(v) is vector<int>
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    decltype(v[0]) v0 = x;      // decltype(v[0]) is int&

    int& returnTest1 = MethodTest11(v, 0);
    MethodTest11(v, 0) = 5;

    int& returnTest2 = MethodTest14(v, 0);
    MethodTest14(v, 0) = 5;


    {
        struct WidgetDeclType
        {
        };

        WidgetDeclType w;

        const WidgetDeclType& cw = w;

        auto myWidget1 = cw;             // auto type deduction:
                                         // myWidget1's type is WidgetDeclType

        decltype(auto) myWidget2 = cw;   // decltype type deduction:
                                         // myWidget2's type is
                                         //   const WidgetDeclType&

    }

    {
        int x = 0;
        decltype(x) x1 = x;     //x1 is int
        decltype( (x) ) x2 = x; //x2 is int&
        ++x2;
        ++x2;
    }
END_TEST()
