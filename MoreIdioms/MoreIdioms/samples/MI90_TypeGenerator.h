#pragma once
#include "stdafx.h"
#include <map>

/*
typedef 
    std::map <std::string, int, less<std::string>, __gnu_cxx::malloc_allocator<std::string> > 
DirectoryInt;

typedef 
    std::map <std::string, float, less<std::string>, __gnu_cxx::malloc_allocator<std::string> > 
    DirectoryInt;

*/

template <class Value>
struct Directory
{
    typedef std::map <    std::string
                        , Value
                        , std::less<std::string>
                      > 
    type;
};


BEGIN_TEST(TypeGenerator)
    Directory<int>::type a;   // gives a map of string to integers.
    Directory<float>::type b;  // gives a map of string to floats.
END_TEST()


