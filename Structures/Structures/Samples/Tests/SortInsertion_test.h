#pragma once
#include "stdafx.h"
#include "Samples/SortInsertion.h"

BEGIN_TEST(TestInsertionSort)
		static const unsigned int MAX = 1000;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		InsertionSort<int>::Print( list, MAX );
		InsertionSort<int>::Execute( list, MAX );
		InsertionSort<int>::Print( list, MAX );
END_TEST()