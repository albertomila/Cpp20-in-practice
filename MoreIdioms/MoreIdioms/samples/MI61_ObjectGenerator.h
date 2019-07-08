#pragma once
#include "stdafx.h"

#include <map>

template <class T, class U>
std::pair <T, U> MakePair(T t, U u)
{
    return std::pair <T, U> (t,u);
}


BEGIN_TEST(ObjectGemerator)
    std::map <int, double> m;
    m.insert (MakePair(1,1.0)); // No need to know how pair template is instantiated.
    m.insert (MakePair(1,1.0));
    m.insert (MakePair(1,1.0));
    m.insert (MakePair(1,1.0));
    m.insert (MakePair(1,1.0));
    m.insert (MakePair(1,1.0));
END_TEST()