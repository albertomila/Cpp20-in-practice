#pragma once
#include "stdafx.h"
#include "Samples/SortBubble.h"

BEGIN_TEST(TestBubbleSort)
		static const unsigned int MAX = 10000;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAX;
		}

		BubbleSort<int>::Print( list, MAX );
		BubbleSort<int>::Execute( list, MAX );
		BubbleSort<int>::Print( list, MAX );
END_TEST()