#pragma once
#include "stdafx.h"
#include <algorithm>

class String
{
    char* m_str;
public:

    String( const char* value )
    {
        m_str = new char[32];
		SafeStrCopy( m_str, value );
    }

    ~String()
    {
        delete m_str;
    }

    String & operator = (String const &s)
    {
        if (this != &s)
        {
            String s2(s);
            s2.swap (*this); // Copy-constructor and non-throwing swap
        }

        // Old resources are released with the destruction of the temporary above
        return *this;
    }

    void swap (String &s) throw () // Also see non-throwing swap idiom
    {
        std::swap(this->m_str, s.m_str);
    }
};


BEGIN_TEST(CopyAndSwap)
    String s1( "test1" );
    String s2( "99999" );

    s2 = s1;

	END_TEST()