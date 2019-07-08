#pragma once
#include "stdafx.h"

///////////////////////////////////////////////////////////////

BEGIN_TEST(ShrinkToFit)
    std::vector<int> list;

    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );
    list.push_back( 3 );
    list.push_back( 4 );
    list.push_back( 5 );
    list.push_back( 6 );
    list.push_back( 7 );
    list.push_back( 8 );
    list.push_back( 9 );
    list.erase( list.begin() );
    list.erase( list.begin() );
    list.erase( list.begin() );
    list.erase( list.begin() );
    list.erase( list.begin() );

    //v is swapped with its temporary copy, which is capacity optimal
    std::vector<int>(list).swap(list);
	
	std::vector<int>(list).shrink_to_fit(); //C++11

    //v is swapped with its temporary copy, which is capacity optimal
    //std::vector<int>( list.begin(), list.end()).swap( list );

	END_TEST()