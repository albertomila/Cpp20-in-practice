#pragma once
#include "stdafx.h"
///////////////////////////////////////////////////////////////
class NonCopyable
{
protected:
    NonCopyable () {}
    ~NonCopyable () {} /// Protected non-virtual destructor
private: 
    NonCopyable (const NonCopyable &);
    NonCopyable & operator = (const NonCopyable &);
};

class CantCopy : private NonCopyable
{
};

///////////////////////////////////////////////////////////////
template <class T>
class NonCopyableT
{
protected:
    NonCopyableT () {}
    ~NonCopyableT () {} /// Protected non-virtual destructor
private: 
    NonCopyableT (const NonCopyableT &);
    NonCopyableT & operator = (const NonCopyableT &);
};
class CantCopy2 : private NonCopyableT <CantCopy2>
{
};

///////////////////////////////////////////////////////////////

BEGIN_TEST(NonCopyableTest)
    CantCopy c1, c2;
    //c1 = c2; //compilation error

    CantCopy2 c3, c4;
    //c1 = c2; //compilation error

	END_TEST()