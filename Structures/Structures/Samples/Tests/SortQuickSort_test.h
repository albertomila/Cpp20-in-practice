#pragma once
#include "stdafx.h"
#include "Samples/SortQuickSort.h"
#include <vector>

BEGIN_TEST(TestQuickSort)
		static const unsigned int MAX = 100;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		QuickSort<int>::Execute( list, MAX );
		QuickSort<int>::Print( list, MAX );

		std::vector<int> vec(MAX);

		for( int i = 0; i<MAX; ++i)
		{
			vec[i] = rand() %MAX;
		}

		typedef QuickSort<int, std::vector<int>, ElementAtVector > TMergeSortVector;

		TMergeSortVector::Execute( vec, MAX );
		TMergeSortVector::Print(vec, MAX);
END_TEST()