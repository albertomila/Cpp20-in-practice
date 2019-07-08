#pragma once
#include "stdafx.h"
#include "Samples/arrayHeap.h"
#include "math.h"

BEGIN_TEST(TestArrayHeap)
		TMinHeapArray heap;

		for( int i = 0; i<60; ++i)
		{
			heap.PushValue( rand() % 100 );
			HeapArrayPrintHelpers::Print( heap );
		}

		for( int i = 0; i<60; ++i)
		{
			heap.RemoveTop();
			HeapArrayPrintHelpers::Print( heap );
		}
END_TEST()