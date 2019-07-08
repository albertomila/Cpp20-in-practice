#pragma once
#include "stdafx.h"
#include "Samples/SortSelection.h"

BEGIN_TEST(TestSelectionSort)
		static const unsigned int MAX = 1000;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		SelectionSort<int>::Print( list, MAX );
		SelectionSort<int>::Execute( list, MAX );
		SelectionSort<int>::Print( list, MAX );
END_TEST()
