#pragma once
#include "stdafx.h"
////////////////////////////////////////////////////////////
class NamedParameters_Data
{
public:
    int a;
    char b;

    NamedParameters_Data() : a(-999), b('C') {}  // Initialize with default values, if any.
    NamedParameters_Data & setA(int i) { a = i; return *this; } // non-const function
    NamedParameters_Data & setB(char c) { b = c; return *this; } // non-const function

    static NamedParameters_Data create() {
        return NamedParameters_Data();
    }
};

////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream & o, NamedParameters_Data const & x)
{
    o << x.a << " " << x.b;
    return o;
}
////////////////////////////////////////////////////////////

BEGIN_TEST(NamedParameters)
    // The following code uses the named parameter idiom.
    std::cout << NamedParameters_Data::create().setA(10).setB('Z') << std::endl;

END_TEST()