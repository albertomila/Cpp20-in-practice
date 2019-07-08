#pragma once
#include "stdafx.h"
#include "Samples/SortMergeSort.h"
#include "Samples/SortHelpers.h"
#include <vector>

BEGIN_TEST(TestMergerSort)
		static const unsigned int MAX = 10;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		MergerSort<int>::Execute( list, MAX );
		MergerSort<int>::Print( list, MAX );

		std::vector<int> vec(MAX);

		for( int i = 0; i<MAX; ++i)
		{
			vec[i] = rand() %MAX;
		}

		typedef MergerSort<int, std::vector<int>, ElementAtVector > TMergeSortVector;

		TMergeSortVector::Execute( vec, MAX );
		TMergeSortVector::Print( vec, MAX );
END_TEST()