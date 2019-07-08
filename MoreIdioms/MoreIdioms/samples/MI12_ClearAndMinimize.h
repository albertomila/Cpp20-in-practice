#pragma once
#include "stdafx.h"

BEGIN_TEST(ClearAndMinimize)
    std::vector <int> v;
    //... Lots of push_backs and then lots of remove on v.
    v.push_back( 1 );
    v.push_back( 2 );
    v.push_back( 3 );
    v.push_back( 4 );
    v.push_back( 5 );
    v.push_back( 6 );
    v.push_back( 7 );
    v.push_back( 8 );
    v.push_back( 9 );
    v.push_back( 10 );
    v.push_back( 11 );
    v.push_back( 12 );
    v.push_back( 13 );
    v.push_back( 14 );
    v.push_back( 15 );
    v.push_back( 16 );
    v.push_back( 17 );
    v.push_back( 18 );
    v.push_back( 19 );
    v.push_back( 20 );
    v.clear(); //the capacity remains equal
    v.resize( 0 );//the capacity remains equal
    std::vector<int>().swap (v);//it clears the capacity

	END_TEST()
