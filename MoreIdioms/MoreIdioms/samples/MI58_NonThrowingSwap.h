#pragma once
#include "stdafx.h"
/////////////////////////////////////////////////////////////
class UserDefined 
{
    std::string m_str;
public:
    
    UserDefined( const std::string str )
        : m_str( str )
    {
    }

    void swap (UserDefined & u) // throw () 
    { 
        std::swap (m_str, u.m_str); 
    }
};

/////////////////////////////////////////////////////////////
namespace std
{
    // Full specializations of the templates in std namespace can be added in std namespace.
    template <>
    void swap (UserDefined & u1, UserDefined & u2) // throw ()
    {
        u1.swap (u2);
    }
}
/*

/////////////////////////////////////////////////////////////
namespace std
{
    // Full specializations of the templates in std namespace can be added in std namespace.
    template <> 
    void swap (Myclass & m1, Myclass & m2) // throw ()
    {
        m1.swap (m2);
    }
}

/////////////////////////////////////////////////////////////
class Myclass
{
    UserDefined u;
    char * name;
public:
    void swap (Myclass & m) // throw ()
    {
        std::swap (u, m.u);       // cascading use of the idiom due to uniformity
        std::swap (name, m.name); // Ditto here
    }   
};
*/
///////////////////////////////////////////////////////////////

BEGIN_TEST(NonThrowingSwap)
    UserDefined u1( "test1" );
    UserDefined u2( "test2" );

    u1.swap( u2 );
    std::swap( u1, u2 );

	END_TEST()