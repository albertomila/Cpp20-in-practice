#pragma once
#include "stdafx.h"
#include "Samples/SortBucket.h"

BEGIN_TEST(TestBucketSort)
		static const unsigned int MAX = 100;
		static const unsigned int MAXVALUE = 100;
		int* list = new int[MAX];
		for( int i = 0; i<MAX; ++i)
		{
			*(list+i) = rand() %MAXVALUE;
		}

		BucketSort<int,1000>::Print( list, MAX );
		BucketSort<int,MAXVALUE>::Execute( list, MAX );
		BucketSort<int,MAXVALUE>::Print( list, MAX );
END_TEST()