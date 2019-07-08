#pragma once
#include "stdafx.h"
#include <list>

class getRandomN 
{
    size_t count;

public:
    getRandomN(int n = 1) 
        : count(n) 
    {
    }

    //conversion operator funcion
    template <class Container>
    operator Container () 
    {
        Container c;
        for(size_t i = 0;i < count; ++i)
        {
            c.insert(c.end(), rand()); // push_back is not supported by all standard containers.
        }
        return c;
    }

    /*
    operator int()
    {
        return 0;
    }
    */
};


BEGIN_TEST(ReturnType)
//    int x = getRandomN(2);
    std::vector<int> random_v = getRandomN(10);
    std::list<int> random_l = getRandomN(10);
END_TEST()