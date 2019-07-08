#pragma once
#include "stdafx.h"
/////////////////////////////////////////////////
template<class T>
class MakeFinal
{
private:
    MakeFinal() 
    {
        ;
    }  // private by default.
    friend T;
};

#define MAKE_FINAL( T ) virtual MakeFinal<T>
#define FINAL_CLASS( T ) class T : virtual MakeFinal<T>

/////////////////////////////////////////////////
class CFinal : MAKE_FINAL( CFinal )
{
public:
    CFinal() 
    {
        ;
    }  // private by default.
};

/////////////////////////////////////////////////
FINAL_CLASS( CFinal2 )
{
public:
    CFinal2() 
    {
        ;
    }  // private by default.
};
/*
/////////////////////////////////////////////////
class CTest : public CFinal
{
public:
    CTest() 
    {
        ;
    }  // private by default.
};
*/

BEGIN_TEST(FinalClass)
    CFinal s1;
    CFinal2 s2;

    //CTest t;
END_TEST()