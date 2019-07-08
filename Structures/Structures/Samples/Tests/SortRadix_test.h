#pragma once
#include "stdafx.h"
#include "Samples/SortRadix.h"

BEGIN_TEST(TestRadixSort)
		static const unsigned int MAX = 1000;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		RadixSort::Print( list, MAX );
		RadixSort::Execute( list, MAX );
		RadixSort::Print( list, MAX );
END_TEST()