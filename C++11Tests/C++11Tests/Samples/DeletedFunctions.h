#pragma once
#include "stdafx.h"

template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base 
{
public:
    basic_ios(const basic_ios&) = delete;
    basic_ios& operator=(const basic_ios&) = delete;
};

class Widget2 
{
public:
    template<typename T>
    void processPointer(T* ptr)
    {
    }

    //delete void case
    template<>
    void processPointer<void>(void* ptr) = delete;
};

static bool isLucky(int number)
{
    return number == 7;
}
static bool isLucky(char) = delete;         // reject chars
static bool isLucky(bool) = delete;         // reject bools
static bool isLucky(double) = delete;       // reject doubles and floats

BEGIN_TEST(TestDeletedFunctions)
    isLucky(3);
    //isLucky('a'); //error
    //isLucky(true); //error
    //isLucky(3.5f); //error

    Widget2 w;
    w.processPointer<int>(nullptr);
    //w.processPointer<void>(nullptr); // error, reject void
END_TEST()